#!/usr/bin/env python3
"""Compare two generated outputs per project using the locked, read-only AST meter.
Build the meter first with managed Cargo; this script never builds or edits inputs.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
import tempfile

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('compendium_initial', type=Path)
parser.add_argument('compendium_import_fix', type=Path)
parser.add_argument('tau2_initial', type=Path)
parser.add_argument('tau2_import_fix', type=Path)
parser.add_argument('output', type=Path)
parser.add_argument('--meter', required=True, type=Path, help='Built meter/target/debug/anatomy executable')
a = parser.parse_args()
rows, reports, provenance = [], {}, {}
for project, initial, repaired in [
    ('compendium', a.compendium_initial, a.compendium_import_fix),
    ('tau2', a.tau2_initial, a.tau2_import_fix),
]:
    reports[project], provenance[project] = {}, {}
    for snapshot, root in [('initial', initial.resolve()), ('import-fix', repaired.resolve())]:
        report_path = root / 'unsloppifier-report.json'
        report = json.loads(report_path.read_text())
        reports[project][snapshot] = report
        provenance[project][snapshot] = {'normalization_report_sha256': hashlib.sha256(report_path.read_bytes()).hexdigest()}
        for package in report['packages']:
            for rel in package['output_files']:
                path = (root / rel).resolve()
                assert path.is_relative_to(root) and path.suffix == '.rs', rel
                rows.append({'project': project, 'snapshot': snapshot, 'package': package['name'],
                             'path': rel, 'absolute': str(path),
                             'sha256': hashlib.sha256(path.read_bytes()).hexdigest()})
with tempfile.TemporaryDirectory(prefix='import-fix-meter-') as temporary:
    manifest = Path(temporary) / 'manifest.json'
    manifest.write_text(json.dumps(rows))
    measured = json.loads(subprocess.check_output([str(a.meter.resolve()), str(manifest)]))

summary = {}
for project, versions in reports.items():
    totals = {}
    for snapshot in ('initial', 'import-fix'):
        rs = [r for r in measured if r['project'] == project and r['snapshot'] == snapshot]
        totals[snapshot] = {key: sum(row[key] for row in rs) for key in ('physical_lines', 'formatted_lines', 'tokens')}
        totals[snapshot]['anatomy'] = {key: sum(row['anatomy'][key] for row in rs) for key in rs[0]['anatomy']}
    previous, current = totals['initial'], totals['import-fix']
    initial, repaired = versions['initial'], versions['import-fix']
    current['inlinings'] = len(repaired['inlining']['inlined'])
    current['dead_removed'] = len(repaired['inlining']['removed_dead'])
    current['same_inlined_function_set'] = set(initial['inlining']['inlined']) == set(repaired['inlining']['inlined'])
    current['same_removed_function_set'] = set(initial['inlining']['removed_dead']) == set(repaired['inlining']['removed_dead'])
    current['suspended_items'] = {p['name']: p['suspended_test_items'] for p in repaired['packages']}
    assert current['same_inlined_function_set'] and current['same_removed_function_set']
    assert current['suspended_items'] == {p['name']: p['suspended_test_items'] for p in initial['packages']}
    summary[project] = {'original_generated_output': previous, 'import_fix_output': current,
                        'reductions': {key: previous[key] - current[key] for key in ('physical_lines', 'formatted_lines', 'tokens')}}
summary['scope'] = ('Full-pipeline reruns; only import generation changed. Accepted inline/dead-removal sets '
                    'and suspension counts match the first outputs. Broader verbosity of inlining frames is not fixed.')
for row in measured:
    row.pop('absolute', None)
a.output.parent.mkdir(parents=True, exist_ok=True)
a.output.write_text(json.dumps({'summary': summary, 'files': measured, 'provenance': provenance}, indent=2) + '\n')
print(json.dumps(summary, indent=2))
