
uint jsmn_parse(uint *param_1,long param_2,ulong param_3,long param_4,uint param_5)

{
  byte bVar1;
  char cVar2;
  undefined1 auVar3 [16];
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  ulong uVar10;
  long lVar11;
  int *piVar12;
  long lVar13;
  uint uVar14;
  bool bVar15;
  
  uVar14 = *param_1;
  uVar6 = param_1[1];
  uVar4 = 0xfffffffe;
LAB_00101b4e:
  if (param_3 <= uVar14) {
LAB_00101fad:
    uVar4 = uVar6;
    if (param_4 != 0) {
      uVar14 = param_1[1];
      do {
        uVar14 = uVar14 - 1;
        if ((int)uVar14 < 0) {
          return uVar6;
        }
        lVar11 = (ulong)(uVar14 & 0x7fffffff) * 0x10;
      } while ((*(int *)(param_4 + 4 + lVar11) == -1) ||
              (uVar4 = 0xfffffffd, *(int *)(lVar11 + param_4 + 8) != -1));
    }
switchD_00101b78_caseD_21:
    return uVar4;
  }
  bVar1 = *(byte *)(param_2 + (ulong)uVar14);
  switch(bVar1) {
  case 0x20:
    break;
  case 0x21:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2e:
  case 0x2f:
    goto switchD_00101b78_caseD_21;
  case 0x22:
    uVar9 = uVar14 + 1;
    do {
      *param_1 = uVar9;
      if (param_3 <= uVar9) goto LAB_00101f91;
      cVar2 = *(char *)(param_2 + (ulong)uVar9);
      uVar7 = uVar9;
      if (cVar2 == '\\') {
        uVar8 = uVar9 + 1;
        if (uVar8 < param_3) {
          *param_1 = uVar8;
          bVar1 = *(byte *)(param_2 + (ulong)uVar8);
          uVar7 = uVar8;
          if ((0x37 < bVar1 - 0x2f) ||
             ((0x88200000000001U >> ((ulong)(bVar1 - 0x2f) & 0x3f) & 1) == 0)) {
            switch(bVar1) {
            case 0x6e:
            case 0x72:
            case 0x74:
              break;
            case 0x6f:
            case 0x70:
            case 0x71:
            case 0x73:
              goto switchD_00101bf1_caseD_6f;
            case 0x75:
              uVar9 = uVar9 + 2;
              iVar5 = 4;
              *param_1 = uVar9;
              while (((bVar15 = iVar5 != 0, iVar5 = iVar5 + -1, bVar15 && (uVar9 < param_3)) &&
                     (bVar1 = *(byte *)(param_2 + (ulong)uVar9), bVar1 != 0))) {
                if ((9 < (byte)(bVar1 - 0x30)) &&
                   ((0x25 < bVar1 - 0x41 ||
                    ((0x3f0000003fU >> ((ulong)(bVar1 - 0x41) & 0x3f) & 1) == 0))))
                goto switchD_00101bf1_caseD_6f;
                uVar9 = uVar9 + 1;
                *param_1 = uVar9;
              }
              *param_1 = uVar9 - 1;
              uVar7 = uVar9 - 1;
              break;
            default:
              if (bVar1 != 0x22) goto switchD_00101bf1_caseD_6f;
            }
          }
        }
      }
      else {
        if (cVar2 == '\0') goto LAB_00101f91;
        if (cVar2 == '\"') goto LAB_00101f43;
      }
      uVar9 = uVar7 + 1;
    } while( true );
  case 0x2c:
    if (((param_4 != 0) && ((long)(int)param_1[2] != -1)) &&
       (1 < *(int *)(param_4 + (long)(int)param_1[2] * 0x10) - 1U)) {
      uVar7 = param_1[1];
      do {
        uVar7 = uVar7 - 1;
        if ((int)uVar7 < 0) goto switchD_00101b78_caseD_20;
        lVar11 = (ulong)(uVar7 & 0x7fffffff) * 0x10;
      } while (((1 < *(int *)(param_4 + lVar11) - 1U) ||
               (lVar11 = lVar11 + param_4, *(int *)(lVar11 + 4) == -1)) ||
              (*(int *)(lVar11 + 8) != -1));
LAB_00101ef5:
      param_1[2] = uVar7;
    }
    break;
  case 0x2d:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x39:
switchD_00101b78_caseD_2d:
    uVar9 = uVar14;
    if ((param_4 != 0) && ((long)(int)param_1[2] != -1)) {
      lVar11 = (long)(int)param_1[2] * 0x10;
      iVar5 = *(int *)(param_4 + lVar11);
      if (iVar5 == 4) {
        if (*(int *)(lVar11 + param_4 + 0xc) != 0) {
          return 0xfffffffe;
        }
      }
      else if (iVar5 == 1) {
        return 0xfffffffe;
      }
    }
    do {
      if (param_3 <= uVar9) goto LAB_00101f91;
      bVar1 = *(byte *)(param_2 + (ulong)uVar9);
      uVar10 = (ulong)bVar1;
      if (uVar10 < 0x2d) {
        if ((0x100100002600U >> (uVar10 & 0x3f) & 1) != 0) goto LAB_00101db3;
        if (uVar10 == 0) goto LAB_00101f91;
      }
      if ((bVar1 == 0x5d) || (bVar1 == 0x7d)) goto LAB_00101db3;
      if ((byte)(bVar1 + 0x81) < 0xa1) goto switchD_00101bf1_caseD_6f;
      *param_1 = uVar9 + 1;
      uVar9 = uVar9 + 1;
    } while( true );
  case 0x3a:
switchD_00101b78_caseD_3a:
    param_1[2] = param_1[1] - 1;
    break;
  default:
    uVar10 = (ulong)(bVar1 - 0x5b);
    if (bVar1 - 0x5b < 0x23) {
      if ((0x2080800UL >> (uVar10 & 0x3f) & 1) != 0) goto switchD_00101b78_caseD_2d;
      if ((0x100000001U >> (uVar10 & 0x3f) & 1) == 0) {
        if ((0x400000004U >> (uVar10 & 0x3f) & 1) == 0) goto LAB_00101d3d;
        if (param_4 != 0) {
          uVar9 = param_1[1];
          do {
            uVar7 = uVar9;
            uVar9 = uVar7 - 1;
            if ((int)uVar9 < 0) goto LAB_00101f15;
            lVar11 = (ulong)(uVar9 & 0x7fffffff) * 0x10;
          } while ((*(int *)(param_4 + 4 + lVar11) == -1) ||
                  (piVar12 = (int *)(lVar11 + param_4), piVar12[2] != -1));
          if (*piVar12 != (bVar1 != 0x7d) + 1) {
            return 0xfffffffe;
          }
          param_1[2] = 0xffffffff;
          piVar12[2] = uVar14 + 1;
LAB_00101f15:
          if (uVar7 == 0) {
            return 0xfffffffe;
          }
          do {
            uVar7 = uVar7 - 1;
            if ((int)uVar7 < 0) goto switchD_00101b78_caseD_20;
          } while ((*(int *)(param_4 + 4 + (ulong)uVar7 * 0x10) == -1) ||
                  (*(int *)((ulong)uVar7 * 0x10 + param_4 + 8) != -1));
          goto LAB_00101ef5;
        }
      }
      else {
        uVar6 = uVar6 + 1;
        if (param_4 != 0) {
          uVar14 = param_1[1];
          if (param_5 <= uVar14) {
            return 0xffffffff;
          }
          lVar11 = (ulong)uVar14 * 0x10;
          param_1[1] = uVar14 + 1;
          *(undefined8 *)(param_4 + 4 + lVar11) = 0xffffffffffffffff;
          *(undefined4 *)(param_4 + 0xc + lVar11) = 0;
          if ((long)(int)param_1[2] != -1) {
            lVar13 = (long)(int)param_1[2] * 0x10;
            if (*(int *)(param_4 + lVar13) == 1) {
              return 0xfffffffe;
            }
            piVar12 = (int *)(lVar13 + param_4 + 0xc);
            *piVar12 = *piVar12 + 1;
          }
          *(int *)(lVar11 + param_4) = (bVar1 != 0x7b) + 1;
          ((int *)(lVar11 + param_4))[1] = *param_1;
          goto switchD_00101b78_caseD_3a;
        }
      }
    }
    else {
LAB_00101d3d:
      if ((1 < bVar1 - 9) && (bVar1 != 0xd)) {
        if (bVar1 != 0) {
          return 0xfffffffe;
        }
        goto LAB_00101fad;
      }
    }
  }
  goto switchD_00101b78_caseD_20;
LAB_00101db3:
  if (param_4 != 0) {
    uVar9 = param_1[1];
    if (param_5 <= uVar9) goto LAB_00101fa4;
    lVar11 = (ulong)uVar9 * 0x10;
    param_1[1] = uVar9 + 1;
    *(undefined8 *)(param_4 + 4 + lVar11) = 0xffffffffffffffff;
    *(undefined4 *)(param_4 + 0xc + lVar11) = 0;
    auVar3 = vpunpckldq_avx(ZEXT416(8),ZEXT416(uVar14));
    auVar3 = vpunpcklqdq_avx(auVar3,ZEXT416(*param_1));
    *(undefined1 (*) [16])(param_4 + lVar11) = auVar3;
    uVar9 = *param_1;
  }
  *param_1 = uVar9 - 1;
  goto LAB_00101e04;
LAB_00101f91:
  uVar4 = 0xfffffffd;
  goto switchD_00101bf1_caseD_6f;
LAB_00101f43:
  if (param_4 != 0) {
    uVar9 = param_1[1];
    if (param_5 <= uVar9) {
LAB_00101fa4:
      uVar4 = 0xffffffff;
switchD_00101bf1_caseD_6f:
      *param_1 = uVar14;
      return uVar4;
    }
    lVar11 = (ulong)uVar9 * 0x10;
    param_1[1] = uVar9 + 1;
    *(undefined8 *)(param_4 + 4 + lVar11) = 0xffffffffffffffff;
    *(undefined4 *)(param_4 + 0xc + lVar11) = 0;
    auVar3 = vpunpckldq_avx(ZEXT416(4),ZEXT416(uVar14 + 1));
    auVar3 = vpunpcklqdq_avx(auVar3,ZEXT416(*param_1));
    *(undefined1 (*) [16])(param_4 + lVar11) = auVar3;
  }
LAB_00101e04:
  uVar6 = uVar6 + 1;
  if ((long)(int)param_1[2] != -1 && param_4 != 0) {
    piVar12 = (int *)(param_4 + 0xc + (long)(int)param_1[2] * 0x10);
    *piVar12 = *piVar12 + 1;
  }
switchD_00101b78_caseD_20:
  uVar14 = *param_1 + 1;
  *param_1 = uVar14;
  goto LAB_00101b4e;
}




void jsmn_init(undefined8 *param_1)

{
  *param_1 = 0;
  *(undefined4 *)(param_1 + 1) = 0xffffffff;
  return;
}



