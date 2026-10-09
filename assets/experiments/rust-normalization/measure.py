#!/usr/bin/env python3
"""Reproduce the report's size metrics. Does not edit the four input trees.
Usage: measure.py COMPENDIUM_INPUT COMPENDIUM_OUTPUT TAU_INPUT TAU_OUTPUT OUTPUT_DIR
Requires installed tokei and the managed Cargo at /usr/local/bin/cargo.
"""
import collections,csv,hashlib,json,pathlib,re,subprocess,sys
roots=list(map(lambda p:pathlib.Path(p).resolve(),sys.argv[1:5]))
out=pathlib.Path(sys.argv[5]).resolve();out.mkdir(parents=True,exist_ok=True)
rows=[];reports={};inputs=[]
for project,before,after in [('compendium',roots[0],roots[1]),('tau2',roots[2],roots[3])]:
 report=json.loads((after/'unsloppifier-report.json').read_text());reports[project]=report
 for snapshot,root in [('before',before),('after',after)]:
  for package in report['packages']:
   for area in ['src','tests','examples','benches']:
    directory=root/package['directory']/area
    for p in sorted(directory.rglob('*.rs')):
     if any(x in ('.git','target') for x in p.relative_to(root).parts):continue
     rows.append(dict(project=project,snapshot=snapshot,package=package['name'],path=str(p.relative_to(root)),absolute=str(p),sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
 paths=[r['absolute']for r in rows if r['project']==project and r['snapshot']=='before']
 assert len(paths)==sum(p['source_files_coalesced']for p in report['packages']), (project,len(paths))
manifest=out/'meter-input-local.json';manifest.write_text(json.dumps(rows))
meter=pathlib.Path(__file__).parent/'meter/Cargo.toml'
with (out/'meter-build.log').open('wb') as log:
 data=subprocess.check_output(['/usr/local/bin/cargo','run','--offline','--quiet','--bin','normalization_report_meter','--manifest-path',str(meter),'--',str(manifest)],stderr=log)
measured=json.loads(data)
# Tokei supplies conventional code/comment/blank line counts on precisely the
# same explicit file list; there is no VCS-ignore or directory-selection drift.
for project in ['compendium','tau2']:
 for snapshot in ['before','after']:
  selected=[r for r in rows if r['project']==project and r['snapshot']==snapshot]
  raw=json.loads(subprocess.check_output(['tokei','--output','json','--files','--type','Rust','--no-ignore','--']+[r['absolute']for r in selected]))
  stats={r['name']:r['stats']for r in raw['Rust']['reports']}
  for source in selected:
   target=next(r for r in measured if (r['project'],r['snapshot'],r['path'])==(project,snapshot,source['path']))
   s=stats[source['absolute']]
   def blob_lines(blob):
    return sum(blob[k] for k in ['code','comments','blanks'])+sum(blob_lines(b)for b in blob.get('blobs',{}).values())
   assert set(s.get('blobs',{})) <= {'Markdown'}, (source['path'],s['blobs'])
   docs=sum(blob_lines(b)for b in s.get('blobs',{}).values())
   target.update(code_lines=s['code'],comment_lines=s['comments']+docs,blank_lines=s['blanks'])
   target['counter_line_delta']=s['code']+s['comments']+s['blanks']+docs-target['physical_lines']
metrics=['physical_lines','nonblank_lines','code_lines','comment_lines','blank_lines','formatted_lines','formatted_nonblank_lines','tokens','bytes']
summary={}
for project,report in reports.items():
 sums={}
 for snapshot in ['before','after']:
  rs=[r for r in measured if r['project']==project and r['snapshot']==snapshot]
  sums[snapshot]={'files':len(rs),**{k:sum(r[k]for r in rs)for k in metrics}}
 sums['change_percent']={k:round((sums['after'][k]/sums['before'][k]-1)*100,3)for k in ['files']+metrics if sums['before'][k]}
 sums['inlined']=len(report['inlining']['inlined']);sums['dead_removed']=len(report['inlining']['removed_dead'])
 sums['traits']=sum(len(p['behaviour_traits'])for p in report['packages'])
 sums['inlining_exceptions']=len(report['inlining']['exceptions'])
 sums['packages']=[]
 for p in report['packages']:
  item={k:p[k]for k in ['name','directory','test_functions','suspended_test_items']};item['traits']=len(p['behaviour_traits'])
  for snapshot in ['before','after']:
   rs=[r for r in measured if r['project']==project and r['snapshot']==snapshot and r['package']==p['name']]
   item[snapshot]={'files':len(rs),**{k:sum(r[k]for r in rs)for k in metrics}}
  sums['packages'].append(item)
 groups=collections.Counter()
 for e in report['exceptions']:
  if not e['reason'].startswith('test item could not migrate'):continue
  d=e['reason'].split('not promoted to public: ',1)[-1]
  if re.search(r'\bprivate\b|is inaccessible|not publicly',d):cat='explicit_privacy'
  elif re.search(r'cannot find|failed to resolve|unresolved import|not found in',d):cat='unresolved_name'
  elif re.search(r'no (?:method named|function or associated item|associated function or constant)',d):cat='unavailable_method'
  else:cat='other'
  groups[cat]+=1
 sums['suspended_item_diagnostic_categories']=dict(groups)
 assert sum(groups.values())==sum(p['suspended_test_items']for p in report['packages'])
 summary[project]=sums
provenance={}
for name,root in [('compendium',roots[0]),('tau2',roots[2])]:
 provenance[name]={'commit':subprocess.check_output(['git','-C',str(root),'rev-parse','HEAD'],text=True).strip(),'git_status':subprocess.check_output(['git','-C',str(root),'status','--short'],text=True)}
 assert not provenance[name]['git_status']
versions={'tokei':subprocess.check_output(['tokei','--version'],text=True).strip(),'meter_cargo_lock_sha256':hashlib.sha256(meter.with_name('Cargo.lock').read_bytes()).hexdigest()}
result={'scope':'Rust target sources under member-package src/tests/examples/benches; all cfg branches and inactive tests included; build scripts and excluded Windows crates measured separately','summary':summary,'provenance':provenance,'versions':versions,'files':measured}
(out/'metrics.json').write_text(json.dumps(result,indent=2)+'\n')
with (out/'files.csv').open('w') as f:
 writer=csv.DictWriter(f,fieldnames=list(measured[0]));writer.writeheader();writer.writerows(measured)
print(json.dumps(summary,indent=2))
