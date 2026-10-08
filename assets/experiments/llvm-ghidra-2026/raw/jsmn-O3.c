
uint jsmn_parse(uint *param_1,long param_2,ulong param_3,long param_4,uint param_5)

{
  uint uVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  bool bVar5;
  undefined1 auVar6 [16];
  uint uVar7;
  ulong uVar8;
  long lVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  int *piVar13;
  uint uVar14;
  uint uVar15;
  int *piVar16;
  uint uVar17;
  long lVar18;
  
  uVar7 = *param_1;
  uVar10 = param_1[1];
joined_r0x00101e44:
  uVar8 = (ulong)uVar7;
  if (param_3 <= uVar8) {
switchD_00101ec0_caseD_0:
    if (param_4 == 0) {
      return uVar10;
    }
    uVar7 = param_1[1] - 1;
    if ((int)uVar7 < 0) {
      return uVar10;
    }
    piVar16 = (int *)((ulong)uVar7 * 0x10 + 8 + param_4);
    lVar18 = (ulong)uVar7 + 1;
    while ((piVar16[-1] == -1 || (*piVar16 != -1))) {
      piVar16 = piVar16 + -4;
      lVar9 = lVar18 + -1;
      bVar5 = lVar18 < 1;
      lVar18 = lVar9;
      if (lVar9 == 0 || bVar5) {
        return uVar10;
      }
    }
    return 0xfffffffd;
  }
  cVar2 = *(char *)(param_2 + uVar8);
  uVar11 = uVar10;
  switch(cVar2) {
  case '\0':
    goto switchD_00101ec0_caseD_0;
  default:
    return 0xfffffffe;
  case '\t':
  case '\n':
  case '\r':
  case ' ':
    break;
  case '\"':
    uVar17 = uVar7 + 1;
    uVar8 = (ulong)uVar17;
    *param_1 = uVar17;
    uVar14 = uVar17;
    if (uVar8 < param_3) {
      do {
        cVar2 = *(char *)(param_2 + uVar8);
        uVar15 = uVar14;
        if (cVar2 == '\\') {
          uVar1 = uVar14 + 1;
          if (uVar1 < param_3) {
            *param_1 = uVar1;
            uVar11 = 0xfffffffe;
            uVar15 = uVar1;
            switch(*(undefined1 *)(param_2 + (ulong)uVar1)) {
            case 0x22:
            case 0x2f:
            case 0x5c:
            case 0x62:
            case 0x66:
            case 0x6e:
            case 0x72:
            case 0x74:
              break;
            default:
              goto switchD_001021ea_caseD_23;
            case 0x75:
              uVar15 = uVar14 + 2;
              *param_1 = uVar15;
              if ((uVar15 < param_3) && (bVar3 = *(byte *)(param_2 + (ulong)uVar15), bVar3 != 0)) {
                if ((9 < (byte)(bVar3 - 0x30)) &&
                   ((0x25 < bVar3 - 0x41 ||
                    ((0x3f0000003fU >> ((ulong)(bVar3 - 0x41) & 0x3f) & 1) == 0))))
                goto switchD_001021ea_caseD_23;
                uVar15 = uVar14 + 3;
                *param_1 = uVar15;
                if ((uVar15 < param_3) && (bVar3 = *(byte *)(param_2 + (ulong)uVar15), bVar3 != 0))
                {
                  if ((9 < (byte)(bVar3 - 0x30)) &&
                     ((0x25 < bVar3 - 0x41 ||
                      ((0x3f0000003fU >> ((ulong)(bVar3 - 0x41) & 0x3f) & 1) == 0))))
                  goto switchD_001021ea_caseD_23;
                  uVar15 = uVar14 + 4;
                  *param_1 = uVar15;
                  if ((uVar15 < param_3) && (bVar3 = *(byte *)(param_2 + (ulong)uVar15), bVar3 != 0)
                     ) {
                    if ((9 < (byte)(bVar3 - 0x30)) &&
                       ((0x25 < bVar3 - 0x41 ||
                        ((0x3f0000003fU >> ((ulong)(bVar3 - 0x41) & 0x3f) & 1) == 0))))
                    goto switchD_001021ea_caseD_23;
                    uVar15 = uVar14 + 5;
                    *param_1 = uVar15;
                    if ((uVar15 < param_3) &&
                       (bVar3 = *(byte *)(param_2 + (ulong)uVar15), bVar3 != 0)) {
                      if ((9 < (byte)(bVar3 - 0x30)) &&
                         ((0x25 < bVar3 - 0x41 ||
                          ((0x3f0000003fU >> ((ulong)(bVar3 - 0x41) & 0x3f) & 1) == 0))))
                      goto switchD_001021ea_caseD_23;
                      uVar15 = uVar14 + 6;
                    }
                  }
                }
              }
              uVar15 = uVar15 - 1;
            }
          }
        }
        else {
          if (cVar2 == '\0') break;
          if (cVar2 == '\"') goto LAB_00102331;
        }
        uVar14 = uVar15 + 1;
        uVar8 = (ulong)uVar14;
        *param_1 = uVar14;
        if (param_3 <= uVar8) break;
      } while( true );
    }
    uVar11 = 0xfffffffd;
    goto switchD_001021ea_caseD_23;
  case ',':
    if ((((param_4 != 0) && ((long)(int)param_1[2] != -1)) &&
        (1 < *(int *)(param_4 + (long)(int)param_1[2] * 0x10) - 1U)) &&
       (uVar7 = param_1[1] - 1, -1 < (int)uVar7)) {
      piVar16 = (int *)((ulong)uVar7 * 0x10 + param_4 + 8);
      uVar8 = (ulong)uVar7;
      do {
        if (((piVar16[-2] - 1U < 2) && (piVar16[-1] != -1)) && (*piVar16 == -1)) goto LAB_00102159;
        piVar16 = piVar16 + -4;
        bVar5 = 0 < (long)uVar8;
        uVar8 = uVar8 - 1;
      } while (bVar5);
    }
    break;
  case '-':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case 'f':
  case 'n':
  case 't':
    if ((param_4 != 0) && ((long)(int)param_1[2] != -1)) {
      lVar18 = (long)(int)param_1[2] * 0x10;
      iVar4 = *(int *)(param_4 + lVar18);
      if (iVar4 == 4) {
        if (*(int *)(lVar18 + param_4 + 0xc) != 0) {
          return 0xfffffffe;
        }
      }
      else if (iVar4 == 1) {
        return 0xfffffffe;
      }
    }
    do {
      bVar3 = *(byte *)(param_2 + uVar8);
      uVar12 = (ulong)bVar3;
      uVar11 = 0xfffffffd;
      if (uVar12 < 0x2d) {
        if ((0x100100002600U >> (uVar12 & 0x3f) & 1) != 0) goto LAB_00101f50;
        if (uVar12 == 0) goto switchD_001021ea_caseD_23;
      }
      if ((bVar3 == 0x5d) || (bVar3 == 0x7d)) goto LAB_00101f50;
      if ((byte)(bVar3 + 0x81) < 0xa1) {
        uVar11 = 0xfffffffe;
        goto switchD_001021ea_caseD_23;
      }
      uVar14 = (int)uVar8 + 1;
      uVar8 = (ulong)uVar14;
      *param_1 = uVar14;
      if (param_3 <= uVar8) goto switchD_001021ea_caseD_23;
    } while( true );
  case ':':
switchD_00101ec0_caseD_3a:
    param_1[2] = param_1[1] - 1;
    uVar11 = uVar10;
    break;
  case '[':
  case '{':
    uVar10 = uVar10 + 1;
    uVar11 = uVar10;
    if (param_4 != 0) {
      uVar7 = param_1[1];
      if (param_5 <= uVar7) {
        return 0xffffffff;
      }
      lVar18 = (ulong)uVar7 * 0x10;
      param_1[1] = uVar7 + 1;
      *(undefined8 *)(param_4 + 4 + lVar18) = 0xffffffffffffffff;
      *(undefined4 *)(param_4 + 0xc + lVar18) = 0;
      if ((long)(int)param_1[2] != -1) {
        lVar9 = (long)(int)param_1[2] * 0x10;
        if (*(int *)(param_4 + lVar9) == 1) {
          return 0xfffffffe;
        }
        piVar16 = (int *)(lVar9 + param_4 + 0xc);
        *piVar16 = *piVar16 + 1;
      }
      *(int *)(lVar18 + param_4) = (cVar2 != '{') + 1;
      ((int *)(lVar18 + param_4))[1] = *param_1;
      goto switchD_00101ec0_caseD_3a;
    }
    break;
  case ']':
  case '}':
    if (param_4 != 0) {
      uVar10 = param_1[1] - 1;
      if ((int)uVar10 < 0) {
        if (param_1[1] == 0) {
          return 0xfffffffe;
        }
      }
      else {
        piVar16 = (int *)((ulong)uVar10 * 0x10 + param_4);
        uVar8 = (ulong)uVar10;
        while ((piVar16[1] == -1 || (piVar16[2] != -1))) {
          piVar16 = piVar16 + -4;
          uVar10 = uVar10 - 1;
          bVar5 = (long)uVar8 < 1;
          uVar8 = uVar8 - 1;
          if (bVar5) {
            return 0xfffffffe;
          }
        }
        if (*piVar16 != (cVar2 != '}') + 1) {
          return 0xfffffffe;
        }
        param_1[2] = 0xffffffff;
        piVar13 = (int *)((ulong)uVar10 * 0x10 + param_4 + 8);
        piVar16[2] = uVar7 + 1;
        uVar8 = uVar8 & 0xffffffff;
        do {
          if ((piVar13[-1] != -1) && (*piVar13 == -1)) goto LAB_00102159;
          piVar13 = piVar13 + -4;
          bVar5 = 0 < (long)uVar8;
          uVar8 = uVar8 - 1;
        } while (bVar5);
      }
    }
  }
  goto switchD_00101ec0_caseD_9;
LAB_00101f50:
  if (param_4 == 0) {
    *param_1 = (int)uVar8 - 1;
    uVar11 = uVar10 + 1;
    goto switchD_00101ec0_caseD_9;
  }
  uVar11 = param_1[1];
  if (param_5 <= uVar11) goto LAB_001023de;
  lVar18 = (ulong)uVar11 * 0x10;
  param_1[1] = uVar11 + 1;
  *(undefined8 *)(param_4 + 4 + lVar18) = 0xffffffffffffffff;
  *(undefined4 *)(param_4 + 0xc + lVar18) = 0;
  auVar6 = vpunpckldq_avx(ZEXT416(8),ZEXT416(uVar7));
  auVar6 = vpunpcklqdq_avx(auVar6,ZEXT416(*param_1));
  *(undefined1 (*) [16])(param_4 + lVar18) = auVar6;
  *param_1 = *param_1 - 1;
  uVar7 = param_1[2];
  goto joined_r0x00101fa5;
LAB_00102159:
  param_1[2] = (uint)uVar8;
  goto switchD_00101ec0_caseD_9;
LAB_00102331:
  if (param_4 == 0) {
    uVar11 = uVar10 + 1;
    goto switchD_00101ec0_caseD_9;
  }
  uVar11 = param_1[1];
  if (param_5 <= uVar11) {
LAB_001023de:
    uVar11 = 0xffffffff;
switchD_001021ea_caseD_23:
    *param_1 = uVar7;
    return uVar11;
  }
  lVar18 = (ulong)uVar11 * 0x10;
  param_1[1] = uVar11 + 1;
  *(undefined8 *)(param_4 + 4 + lVar18) = 0xffffffffffffffff;
  *(undefined4 *)(param_4 + 0xc + lVar18) = 0;
  auVar6 = vpunpckldq_avx(ZEXT416(4),ZEXT416(uVar17));
  auVar6 = vpunpcklqdq_avx(auVar6,ZEXT416(*param_1));
  *(undefined1 (*) [16])(param_4 + lVar18) = auVar6;
  uVar7 = param_1[2];
joined_r0x00101fa5:
  uVar11 = uVar10 + 1;
  if ((long)(int)uVar7 != -1) {
    piVar16 = (int *)(param_4 + 0xc + (long)(int)uVar7 * 0x10);
    *piVar16 = *piVar16 + 1;
    uVar11 = uVar10 + 1;
  }
switchD_00101ec0_caseD_9:
  uVar7 = *param_1 + 1;
  *param_1 = uVar7;
  uVar10 = uVar11;
  goto joined_r0x00101e44;
}




void jsmn_init(undefined8 *param_1)

{
  *param_1 = 0;
  *(undefined4 *)(param_1 + 1) = 0xffffffff;
  return;
}



