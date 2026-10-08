
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * qoi_encode(long param_1,uint *param_2,int *param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [32];
  undefined4 *puVar8;
  char cVar9;
  byte bVar10;
  int iVar11;
  int iVar12;
  byte bVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  byte bVar17;
  char cVar18;
  int iVar19;
  ulong uVar20;
  int iVar21;
  long lVar22;
  int iVar23;
  char cVar24;
  uint uVar25;
  int iVar26;
  uint uVar27;
  undefined4 local_138;
  undefined8 uStack_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 local_118;
  undefined8 uStack_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  undefined8 uStack_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  
  if (((((param_2 != (uint *)0x0) && (param_1 != 0)) && (param_3 != (int *)0x0)) &&
      ((uVar25 = *param_2, uVar25 != 0 && (uVar27 = param_2[1], uVar27 != 0)))) &&
     ((bVar1 = (byte)param_2[2], 0xfd < (byte)(bVar1 - 5) &&
      ((bVar10 = *(byte *)((long)param_2 + 9), bVar10 < 2 &&
       (uVar27 < (uint)(400000000 / (ulong)uVar25))))))) {
    puVar8 = malloc((long)(int)((bVar1 + 1) * uVar27 * uVar25 + 0x16));
    if (puVar8 != (undefined4 *)0x0) {
      iVar26 = uVar27 * uVar25 * (uint)bVar1;
      *puVar8 = 0x66696f71;
      auVar6 = vpshufd_avx(ZEXT416(uVar25),0x50);
      auVar7 = vpermq_avx2(ZEXT1632(auVar6),0x50);
      auVar7 = vpsrlvd_avx2(auVar7,_DAT_001009c0);
      auVar6 = vpshufb_avx(auVar7._0_16_,SUB6416(ZEXT464(0xc080400),0));
      auVar5 = vpshufb_avx(auVar7._16_16_,SUB6416(ZEXT464(0xc080400),0));
      auVar6 = vpunpckldq_avx(auVar6,auVar5);
      *(long *)(puVar8 + 1) = auVar6._0_8_;
      *(byte *)(puVar8 + 3) = bVar1;
      *(byte *)((long)puVar8 + 0xd) = bVar10;
      local_58 = 0;
      uStack_50 = 0;
      uStack_48 = 0;
      uStack_40 = 0;
      local_78 = 0;
      uStack_70 = 0;
      uStack_68 = 0;
      uStack_60 = 0;
      local_98 = 0;
      uStack_90 = 0;
      uStack_88 = 0;
      uStack_80 = 0;
      local_b8 = 0;
      uStack_b0 = 0;
      uStack_a8 = 0;
      uStack_a0 = 0;
      local_d8 = 0;
      uStack_d0 = 0;
      uStack_c8 = 0;
      uStack_c0 = 0;
      local_f8 = 0;
      uStack_f0 = 0;
      uStack_e8 = 0;
      uStack_e0 = 0;
      local_118 = 0;
      uStack_110 = 0;
      uStack_108 = 0;
      uStack_100 = 0;
      _local_138 = 0;
      uStack_130 = 0;
      uStack_128 = 0;
      uStack_120 = 0;
      if (iVar26 < 1) {
        iVar23 = 0xe;
      }
      else {
        iVar11 = 0;
        iVar16 = 0;
        uVar27 = 0;
        iVar23 = 0xe;
        bVar10 = 0;
        bVar13 = 0;
        uVar25 = 0xff;
        do {
          uVar14 = uVar25;
          if (bVar1 == 4) {
            uVar14 = (uint)*(byte *)(param_1 + (iVar16 + 3));
          }
          bVar2 = *(byte *)(param_1 + iVar16);
          bVar3 = *(byte *)(param_1 + 1 + (long)iVar16);
          bVar4 = *(byte *)(param_1 + (iVar16 + 2));
          uVar15 = (uint)bVar3 << 8 | (uint)bVar4 << 0x10 | uVar14 << 0x18 | (uint)bVar2;
          bVar17 = (byte)iVar11;
          if (uVar15 == ((uint)bVar10 | (uint)bVar13 << 8 | uVar27 << 0x10 | uVar25 << 0x18)) {
            if ((iVar26 - (uint)bVar1 == iVar16) || (iVar11 = iVar11 + 1, iVar11 == 0x3e)) {
              iVar11 = 0;
              uVar20 = (ulong)(bVar17 | 0xc0);
              iVar21 = iVar23;
              iVar23 = iVar23 + 1;
              goto LAB_001025df;
            }
          }
          else {
            if (0 < iVar11) {
              iVar11 = 0;
              lVar22 = (long)iVar23;
              iVar23 = iVar23 + 1;
              *(byte *)((long)puVar8 + lVar22) = bVar17 - 1 | 0xc0;
            }
            uVar20 = (ulong)(uVar14 * 0xb +
                             (((uint)bVar3 * 5 + (uint)bVar2 + (uint)bVar2 * 2 + (uint)bVar4 * 8) -
                             (uint)bVar4) & 0x3f);
            iVar21 = iVar23;
            if ((&local_138)[uVar20] == uVar15) {
              iVar23 = iVar23 + 1;
            }
            else {
              *(byte *)(&local_138 + uVar20) = bVar2;
              *(byte *)((long)&local_138 + uVar20 * 4 + 1) = bVar3;
              *(byte *)((long)&local_138 + uVar20 * 4 + 2) = bVar4;
              *(char *)((long)&local_138 + uVar20 * 4 + 3) = (char)uVar14;
              if ((char)uVar14 == (char)uVar25) {
                cVar24 = bVar2 - bVar10;
                cVar18 = bVar3 - bVar13;
                cVar9 = bVar4 - (char)uVar27;
                if ((((byte)(cVar24 + 2U) < 4) && ((byte)(cVar18 + 2U) < 4)) &&
                   (bVar10 = cVar9 + 2, bVar10 < 4)) {
                  uVar20 = (ulong)(byte)(cVar18 * '\x04' + 8U | cVar24 * '\x10' + 0x20U | bVar10 |
                                        0x40);
                  iVar23 = iVar23 + 1;
                }
                else if ((((byte)((cVar24 - cVar18) + 8U) < 0x10) && ((byte)(cVar18 + 0x20U) < 0x40)
                         ) && (bVar10 = (cVar9 - cVar18) + 8, bVar10 < 0x10)) {
                  iVar21 = iVar23 + 1;
                  *(byte *)((long)puVar8 + (long)iVar23) = cVar18 + 0x20U | 0x80;
                  uVar20 = (ulong)(byte)((bVar10 | (cVar24 - cVar18) * '\x10') + 0x80);
                  iVar23 = iVar23 + 2;
                }
                else {
                  *(undefined1 *)((long)puVar8 + (long)iVar23) = 0xfe;
                  *(byte *)((long)puVar8 + (long)(iVar23 + 1)) = bVar2;
                  iVar21 = iVar23 + 3;
                  *(byte *)((long)puVar8 + (long)(iVar23 + 2)) = bVar3;
                  uVar20 = (ulong)bVar4;
                  iVar23 = iVar23 + 4;
                }
              }
              else {
                iVar12 = iVar23 + 2;
                *(undefined1 *)((long)puVar8 + (long)iVar23) = 0xff;
                iVar21 = iVar23 + 4;
                *(byte *)((long)puVar8 + (long)(iVar23 + 1)) = bVar2;
                iVar19 = iVar23 + 3;
                iVar23 = iVar23 + 5;
                *(byte *)((long)puVar8 + (long)iVar12) = bVar3;
                uVar20 = (ulong)uVar14;
                *(byte *)((long)puVar8 + (long)iVar19) = bVar4;
              }
            }
LAB_001025df:
            *(char *)((long)puVar8 + (long)iVar21) = (char)uVar20;
          }
          uVar27 = (uint)bVar4;
          iVar16 = iVar16 + (uint)bVar1;
          bVar10 = bVar2;
          bVar13 = bVar3;
          uVar25 = uVar14;
        } while (iVar16 < iVar26);
      }
      *(undefined1 *)((long)puVar8 + (long)iVar23) = 0;
      *(undefined4 *)((long)puVar8 + (long)(iVar23 + 1)) = 0;
      *(undefined2 *)((long)puVar8 + (long)(iVar23 + 5)) = 0;
      *(undefined1 *)((long)puVar8 + (long)(iVar23 + 7)) = 1;
      *param_3 = iVar23 + 8;
      return puVar8;
    }
  }
                    /* WARNING: Read-only address (ram,0x001009c0) is written */
  return (undefined4 *)0x0;
}




void * qoi_decode(undefined4 *param_1,int param_2,undefined4 *param_3,uint param_4)

{
  undefined4 uVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  uint uVar8;
  ulong uVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  long lVar13;
  uint uVar14;
  byte bVar15;
  undefined1 auVar16 [16];
  ulong local_150;
  undefined1 local_138 [32];
  undefined1 local_118 [32];
  undefined1 local_f8 [32];
  undefined1 local_d8 [32];
  undefined1 local_b8 [32];
  undefined1 local_98 [32];
  undefined1 local_78 [32];
  undefined1 local_58 [32];
  
  if ((param_1 != (undefined4 *)0x0) && (param_3 != (undefined4 *)0x0)) {
    if ((0x15 < param_2) && (param_4 == 3 || (param_4 & 0xfffffffb) == 0)) {
      uVar4 = param_1[1];
      uVar1 = *param_1;
      *param_3 = CONCAT13((char)uVar4,
                          CONCAT12((char)(uVar4 >> 8),
                                   CONCAT11((char)(uVar4 >> 0x10),(char)(uVar4 >> 0x18))));
      uVar8 = uVar4 >> 0x18 | (uVar4 & 0xff0000) >> 8 | (uVar4 & 0xff00) << 8 | uVar4 << 0x18;
      uVar4 = param_1[2];
      param_3[1] = CONCAT13((char)uVar4,
                            CONCAT12((char)(uVar4 >> 8),
                                     CONCAT11((char)(uVar4 >> 0x10),(char)(uVar4 >> 0x18))));
      bVar10 = *(byte *)(param_1 + 3);
      *(byte *)(param_3 + 2) = bVar10;
      bVar11 = *(byte *)((long)param_1 + 0xd);
      *(byte *)((long)param_3 + 9) = bVar11;
      if (((uVar8 != 0) &&
          (uVar4 = uVar4 >> 0x18 | (uVar4 & 0xff0000) >> 8 | (uVar4 & 0xff00) << 8 | uVar4 << 0x18,
          uVar4 != 0)) && (0xfd < (byte)(bVar10 - 5))) {
        if (1 < bVar11) {
          return (void *)0x0;
        }
        if (CONCAT13((char)uVar1,
                     CONCAT12((char)((uint)uVar1 >> 8),
                              CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18)))) !=
            0x716f6966) {
          return (void *)0x0;
        }
        if (uVar4 < (uint)(400000000 / (ulong)uVar8)) {
          uVar14 = (uint)bVar10;
          if (param_4 != 0) {
            uVar14 = param_4;
          }
          iVar5 = uVar4 * uVar8 * uVar14;
          pvVar2 = malloc((long)iVar5);
          if (pvVar2 != (void *)0x0) {
            auVar16._0_12_ = ZEXT812(0);
            auVar16._12_4_ = 0;
            local_58 = ZEXT1632(auVar16);
            local_78 = ZEXT1632(auVar16);
            local_98 = ZEXT1632(auVar16);
            local_b8 = local_98;
            local_d8 = local_98;
            local_f8 = local_98;
            local_118 = ZEXT1632(auVar16);
            local_138 = ZEXT1632(auVar16);
            if (iVar5 < 1) {
              return pvVar2;
            }
            iVar3 = 0xe;
            bVar7 = 0xff;
            uVar4 = 0;
            iVar6 = 0;
            bVar12 = 0;
            bVar11 = 0;
            bVar10 = 0;
            do {
              if ((int)uVar4 < 1) {
                uVar4 = 0;
                if (iVar3 < param_2 + -8) {
                  lVar13 = (long)iVar3;
                  local_150 = lVar13 + 1;
                  bVar15 = *(byte *)((long)param_1 + lVar13);
                  uVar9 = (ulong)bVar15;
                  if (bVar15 == 0xff) {
                    uVar4 = iVar3 + 5;
                    bVar10 = *(byte *)((long)param_1 + local_150);
                    bVar11 = *(byte *)((long)param_1 + lVar13 + 2);
                    bVar12 = *(byte *)((long)param_1 + lVar13 + 3);
                    bVar7 = *(byte *)((long)param_1 + lVar13 + 4);
LAB_00102a99:
                    local_150 = (ulong)uVar4;
                    uVar4 = 0;
                  }
                  else {
                    if (bVar15 == 0xfe) {
                      uVar4 = iVar3 + 4;
                      bVar10 = *(byte *)((long)param_1 + local_150);
                      bVar11 = *(byte *)((long)param_1 + lVar13 + 2);
                      bVar12 = *(byte *)((long)param_1 + lVar13 + 3);
                      goto LAB_00102a99;
                    }
                    switch(bVar15) {
                    default:
                      bVar10 = local_138[uVar9 * 4];
                      bVar11 = local_138[uVar9 * 4 + 1];
                      bVar12 = local_138[uVar9 * 4 + 2];
                      bVar7 = local_138[uVar9 * 4 + 3];
                      uVar4 = 0;
                      break;
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x43:
                    case 0x44:
                    case 0x45:
                    case 0x46:
                    case 0x47:
                    case 0x48:
                    case 0x49:
                    case 0x4a:
                    case 0x4b:
                    case 0x4c:
                    case 0x4d:
                    case 0x4e:
                    case 0x4f:
                    case 0x50:
                    case 0x51:
                    case 0x52:
                    case 0x53:
                    case 0x54:
                    case 0x55:
                    case 0x56:
                    case 0x57:
                    case 0x58:
                    case 0x59:
                    case 0x5a:
                    case 0x5b:
                    case 0x5c:
                    case 0x5d:
                    case 0x5e:
                    case 0x5f:
                    case 0x60:
                    case 0x61:
                    case 0x62:
                    case 99:
                    case 100:
                    case 0x65:
                    case 0x66:
                    case 0x67:
                    case 0x68:
                    case 0x69:
                    case 0x6a:
                    case 0x6b:
                    case 0x6c:
                    case 0x6d:
                    case 0x6e:
                    case 0x6f:
                    case 0x70:
                    case 0x71:
                    case 0x72:
                    case 0x73:
                    case 0x74:
                    case 0x75:
                    case 0x76:
                    case 0x77:
                    case 0x78:
                    case 0x79:
                    case 0x7a:
                    case 0x7b:
                    case 0x7c:
                    case 0x7d:
                    case 0x7e:
                    case 0x7f:
                      uVar4 = 0;
                      bVar12 = (bVar12 + (bVar15 & 3)) - 2;
                      bVar10 = (bVar10 + (bVar15 >> 4 & 3)) - 2;
                      bVar11 = (bVar11 + (bVar15 >> 2 & 3)) - 2;
                      break;
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8a:
                    case 0x8b:
                    case 0x8c:
                    case 0x8d:
                    case 0x8e:
                    case 0x8f:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9a:
                    case 0x9b:
                    case 0x9c:
                    case 0x9d:
                    case 0x9e:
                    case 0x9f:
                    case 0xa0:
                    case 0xa1:
                    case 0xa2:
                    case 0xa3:
                    case 0xa4:
                    case 0xa5:
                    case 0xa6:
                    case 0xa7:
                    case 0xa8:
                    case 0xa9:
                    case 0xaa:
                    case 0xab:
                    case 0xac:
                    case 0xad:
                    case 0xae:
                    case 0xaf:
                    case 0xb0:
                    case 0xb1:
                    case 0xb2:
                    case 0xb3:
                    case 0xb4:
                    case 0xb5:
                    case 0xb6:
                    case 0xb7:
                    case 0xb8:
                    case 0xb9:
                    case 0xba:
                    case 0xbb:
                    case 0xbc:
                    case 0xbd:
                    case 0xbe:
                    case 0xbf:
                      bVar15 = bVar15 & 0x3f;
                      uVar4 = iVar3 + 2;
                      bVar11 = (bVar11 + bVar15) - 0x20;
                      bVar10 = bVar10 + ((*(byte *)((long)param_1 + local_150) >> 4) - 0x28) +
                                        bVar15;
                      bVar12 = bVar12 + ((*(byte *)((long)param_1 + local_150) & 0xf) - 0x28) +
                                        bVar15;
                      goto LAB_00102a99;
                    case 0xc0:
                    case 0xc1:
                    case 0xc2:
                    case 0xc3:
                    case 0xc4:
                    case 0xc5:
                    case 0xc6:
                    case 199:
                    case 200:
                    case 0xc9:
                    case 0xca:
                    case 0xcb:
                    case 0xcc:
                    case 0xcd:
                    case 0xce:
                    case 0xcf:
                    case 0xd0:
                    case 0xd1:
                    case 0xd2:
                    case 0xd3:
                    case 0xd4:
                    case 0xd5:
                    case 0xd6:
                    case 0xd7:
                    case 0xd8:
                    case 0xd9:
                    case 0xda:
                    case 0xdb:
                    case 0xdc:
                    case 0xdd:
                    case 0xde:
                    case 0xdf:
                    case 0xe0:
                    case 0xe1:
                    case 0xe2:
                    case 0xe3:
                    case 0xe4:
                    case 0xe5:
                    case 0xe6:
                    case 0xe7:
                    case 0xe8:
                    case 0xe9:
                    case 0xea:
                    case 0xeb:
                    case 0xec:
                    case 0xed:
                    case 0xee:
                    case 0xef:
                    case 0xf0:
                    case 0xf1:
                    case 0xf2:
                    case 0xf3:
                    case 0xf4:
                    case 0xf5:
                    case 0xf6:
                    case 0xf7:
                    case 0xf8:
                    case 0xf9:
                    case 0xfa:
                    case 0xfb:
                    case 0xfc:
                    case 0xfd:
                      uVar4 = bVar15 & 0x3f;
                    }
                  }
                  uVar9 = (ulong)((uint)bVar7 * 0xb +
                                  (uint)bVar11 + (uint)bVar11 * 4 + (uint)bVar10 + (uint)bVar10 * 2
                                  + (uint)bVar12 * 7 & 0x3f);
                  local_138[uVar9 * 4] = bVar10;
                  local_138[uVar9 * 4 + 1] = bVar11;
                  local_138[uVar9 * 4 + 2] = bVar12;
                  local_138[uVar9 * 4 + 3] = bVar7;
                  iVar3 = (int)local_150;
                }
              }
              else {
                uVar4 = uVar4 - 1;
              }
              *(byte *)((long)pvVar2 + (long)iVar6) = bVar10;
              *(byte *)((long)pvVar2 + (long)iVar6 + 1) = bVar11;
              *(byte *)((long)pvVar2 + (long)(iVar6 + 2)) = bVar12;
              if (uVar14 == 4) {
                *(byte *)((long)pvVar2 + (long)(iVar6 + 3)) = bVar7;
              }
              iVar6 = iVar6 + uVar14;
              if (iVar5 <= iVar6) {
                return pvVar2;
              }
            } while( true );
          }
        }
      }
    }
  }
  return (void *)0x0;
}



