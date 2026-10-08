
undefined4 * qoi_encode(long param_1,uint *param_2,int *param_3)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  long lVar13;
  byte bVar14;
  char cVar15;
  int iVar16;
  int iVar17;
  byte bVar18;
  byte bVar19;
  byte bVar20;
  byte bVar21;
  char cVar22;
  ulong uVar23;
  undefined1 auVar24 [16];
  int local_144;
  int *local_140;
  undefined1 local_138 [32];
  undefined1 local_118 [32];
  undefined1 local_f8 [32];
  undefined1 local_d8 [32];
  undefined1 local_b8 [32];
  undefined1 local_98 [32];
  undefined1 local_78 [32];
  undefined1 local_58 [32];
  
  if (param_2 == (uint *)0x0) {
    return (undefined4 *)0x0;
  }
  if (param_1 == 0) {
    return (undefined4 *)0x0;
  }
  if (param_3 == (int *)0x0) {
    return (undefined4 *)0x0;
  }
  uVar8 = *param_2;
  if ((((uVar8 != 0) && (uVar5 = param_2[1], uVar5 != 0)) &&
      (bVar1 = (byte)param_2[2], 0xfd < (byte)(bVar1 - 5))) &&
     (bVar19 = *(byte *)((long)param_2 + 9), bVar19 < 2)) {
    if ((uint)(400000000 / (ulong)uVar8) <= uVar5) {
      return (undefined4 *)0x0;
    }
    local_140 = param_3;
    puVar11 = malloc((long)(int)((bVar1 + 1) * uVar5 * uVar8 + 0x16));
    if (puVar11 != (undefined4 *)0x0) {
      iVar9 = 0;
      *puVar11 = 0x66696f71;
      local_144 = 4;
      qoi_write_32(puVar11,&local_144,uVar8);
      qoi_write_32(puVar11,&local_144,uVar5);
      auVar24._0_12_ = ZEXT812(0);
      auVar24._12_4_ = 0;
      local_58 = ZEXT1632(auVar24);
      local_78 = ZEXT1632(auVar24);
      local_98 = ZEXT1632(auVar24);
      local_b8 = local_98;
      local_d8 = local_98;
      local_f8 = local_98;
      local_118 = ZEXT1632(auVar24);
      local_138 = ZEXT1632(auVar24);
      iVar16 = uVar5 * uVar8 * (uint)bVar1;
      *(byte *)((long)puVar11 + (long)local_144) = bVar1;
      iVar7 = local_144 + 2;
      iVar12 = 0;
      *(byte *)((long)puVar11 + (long)(local_144 + 1)) = bVar19;
      bVar14 = 0xff;
      bVar18 = 0;
      bVar19 = 0;
      bVar6 = 0;
      do {
        if (iVar16 <= iVar12) {
          for (lVar13 = 0; iVar9 = iVar7 + (int)lVar13, lVar13 != 8; lVar13 = lVar13 + 1) {
            *(undefined1 *)((long)puVar11 + (long)iVar9) = (&qoi_padding)[lVar13];
          }
          *local_140 = iVar9;
          return puVar11;
        }
        bVar20 = bVar14;
        if (bVar1 == 4) {
          bVar20 = *(byte *)(param_1 + (iVar12 + 3));
        }
        bVar2 = *(byte *)(param_1 + iVar12);
        bVar3 = *(byte *)(param_1 + 1 + (long)iVar12);
        bVar4 = *(byte *)(param_1 + (iVar12 + 2));
        uVar8 = (uint)bVar3 << 8 | (uint)bVar4 << 0x10 | (uint)bVar20 << 0x18 | (uint)bVar2;
        bVar21 = (byte)iVar9;
        if (uVar8 == ((uint)bVar18 | (uint)bVar19 << 8 | (uint)bVar6 << 0x10 | (uint)bVar14 << 0x18)
           ) {
          if ((iVar16 - (uint)bVar1 == iVar12) || (iVar9 = iVar9 + 1, iVar9 == 0x3e)) {
            uVar23 = (ulong)(bVar21 | 0xc0);
            iVar9 = 0;
LAB_001022b6:
            iVar10 = iVar7 + 1;
            iVar17 = iVar7;
            bVar19 = (byte)uVar23;
            goto LAB_0010238c;
          }
        }
        else {
          if (0 < iVar9) {
            iVar9 = 0;
            lVar13 = (long)iVar7;
            iVar7 = iVar7 + 1;
            *(byte *)((long)puVar11 + lVar13) = bVar21 - 1 | 0xc0;
          }
          uVar23 = (ulong)((uint)bVar20 * 0xb +
                           (uint)bVar3 + (uint)bVar3 * 4 + (uint)bVar2 + (uint)bVar2 * 2 +
                           (uint)bVar4 * 7 & 0x3f);
          if (*(uint *)(local_138 + uVar23 * 4) == uVar8) goto LAB_001022b6;
          lVar13 = (long)iVar7;
          local_138[uVar23 * 4] = bVar2;
          local_138[uVar23 * 4 + 1] = bVar3;
          local_138[uVar23 * 4 + 2] = bVar4;
          local_138[uVar23 * 4 + 3] = bVar20;
          if (bVar20 == bVar14) {
            cVar22 = bVar3 - bVar19;
            cVar15 = bVar2 - bVar18;
            if ((((byte)(cVar15 + 2U) < 4) && ((byte)(cVar22 + 2U) < 4)) &&
               (bVar19 = (bVar4 - bVar6) + 2, bVar19 < 4)) {
              iVar10 = iVar7 + 1;
              iVar17 = iVar7;
              bVar19 = cVar22 * '\x04' + 8U | cVar15 * '\x10' + 0x20U | bVar19 | 0x40;
            }
            else if ((((byte)((cVar15 - cVar22) + 8U) < 0x10) && ((byte)(cVar22 + 0x20U) < 0x40)) &&
                    (bVar19 = ((bVar4 - bVar6) - cVar22) + 8, bVar19 < 0x10)) {
              *(byte *)((long)puVar11 + lVar13) = cVar22 + 0x20U | 0x80;
              iVar10 = iVar7 + 2;
              iVar17 = iVar7 + 1;
              bVar19 = (bVar19 | (cVar15 - cVar22) * '\x10') + 0x80;
            }
            else {
              *(undefined1 *)((long)puVar11 + lVar13) = 0xfe;
              iVar10 = iVar7 + 4;
              *(byte *)((long)puVar11 + (long)(iVar7 + 1)) = bVar2;
              *(byte *)((long)puVar11 + (long)(iVar7 + 2)) = bVar3;
              iVar17 = iVar7 + 3;
              bVar19 = bVar4;
            }
          }
          else {
            *(undefined1 *)((long)puVar11 + lVar13) = 0xff;
            *(byte *)((long)puVar11 + (long)(iVar7 + 1)) = bVar2;
            *(byte *)((long)puVar11 + (long)(iVar7 + 2)) = bVar3;
            iVar17 = iVar7 + 4;
            iVar10 = iVar7 + 5;
            *(byte *)((long)puVar11 + (long)(iVar7 + 3)) = bVar4;
            bVar19 = bVar20;
          }
LAB_0010238c:
          *(byte *)((long)puVar11 + (long)iVar17) = bVar19;
          iVar7 = iVar10;
        }
        iVar12 = iVar12 + (uint)bVar1;
        bVar14 = bVar20;
        bVar18 = bVar2;
        bVar19 = bVar3;
        bVar6 = bVar4;
      } while( true );
    }
  }
  return (undefined4 *)0x0;
}




void qoi_write_32(long param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = *param_2;
  *param_2 = iVar1 + 1;
  *(char *)(param_1 + iVar1) = (char)((uint)param_3 >> 0x18);
  iVar1 = *param_2;
  *param_2 = iVar1 + 1;
  *(char *)(param_1 + iVar1) = (char)((uint)param_3 >> 0x10);
  iVar1 = *param_2;
  *param_2 = iVar1 + 1;
  *(char *)(param_1 + iVar1) = (char)((uint)param_3 >> 8);
  iVar1 = *param_2;
  *param_2 = iVar1 + 1;
  *(char *)(param_1 + iVar1) = (char)param_3;
  return;
}




void * qoi_decode(long param_1,int param_2,uint *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  void *pvVar4;
  int iVar5;
  long lVar6;
  byte bVar7;
  uint uVar8;
  byte bVar9;
  ulong uVar10;
  byte bVar11;
  byte bVar12;
  int iVar13;
  byte bVar14;
  undefined1 auVar15 [16];
  ulong local_158;
  int local_144 [3];
  undefined1 local_138 [32];
  undefined1 local_118 [32];
  undefined1 local_f8 [32];
  undefined1 local_d8 [32];
  undefined1 local_b8 [32];
  undefined1 local_98 [32];
  undefined1 local_78 [32];
  undefined1 local_58 [32];
  
  local_144[0] = 0;
  if ((param_1 != 0) && (param_3 != (uint *)0x0)) {
    if ((0x15 < param_2) && (param_4 == 3 || (param_4 & 0xfffffffb) == 0)) {
      iVar1 = qoi_read_32(param_1,local_144);
      uVar2 = qoi_read_32(param_1,local_144);
      *param_3 = uVar2;
      uVar3 = qoi_read_32(param_1,local_144);
      iVar13 = local_144[0];
      param_3[1] = uVar3;
      bVar7 = *(byte *)(param_1 + local_144[0]);
      *(byte *)(param_3 + 2) = bVar7;
      bVar14 = *(byte *)(param_1 + (local_144[0] + 1));
      *(byte *)((long)param_3 + 9) = bVar14;
      if (((uVar2 != 0) && (uVar3 != 0)) && (0xfd < (byte)(bVar7 - 5))) {
        if (1 < bVar14) {
          return (void *)0x0;
        }
        if (iVar1 != 0x716f6966) {
          return (void *)0x0;
        }
        if ((uint)(400000000 / (ulong)uVar2) <= uVar3) {
          return (void *)0x0;
        }
        uVar8 = (uint)bVar7;
        if (param_4 != 0) {
          uVar8 = param_4;
        }
        iVar1 = uVar3 * uVar2 * uVar8;
        pvVar4 = malloc((long)iVar1);
        uVar2 = 0;
        if (pvVar4 != (void *)0x0) {
          iVar13 = iVar13 + 2;
          bVar7 = 0xff;
          auVar15._0_12_ = ZEXT812(0);
          auVar15._12_4_ = 0;
          local_58 = ZEXT1632(auVar15);
          local_78 = ZEXT1632(auVar15);
          local_98 = ZEXT1632(auVar15);
          local_b8 = local_98;
          local_d8 = local_98;
          local_f8 = local_98;
          local_118 = ZEXT1632(auVar15);
          local_138 = ZEXT1632(auVar15);
          bVar14 = 0;
          bVar11 = 0;
          bVar12 = 0;
          iVar5 = 0;
          do {
            if (iVar1 <= iVar5) {
              return pvVar4;
            }
            if ((int)uVar2 < 1) {
              uVar2 = 0;
              if (iVar13 < param_2 + -8) {
                lVar6 = (long)iVar13;
                bVar9 = *(byte *)(param_1 + lVar6);
                uVar10 = (ulong)bVar9;
                local_158 = lVar6 + 1;
                if (bVar9 == 0xff) {
                  bVar14 = *(byte *)(param_1 + local_158);
                  bVar11 = *(byte *)(param_1 + 2 + lVar6);
                  bVar12 = *(byte *)(param_1 + 3 + lVar6);
                  bVar7 = *(byte *)(param_1 + 4 + lVar6);
                  uVar2 = iVar13 + 5;
LAB_00102690:
                  local_158 = (ulong)uVar2;
                  uVar2 = 0;
                }
                else {
                  switch(bVar9) {
                  case 0:
                  case 1:
                  case 2:
                  case 3:
                  case 4:
                  case 5:
                  case 6:
                  case 7:
                  case 8:
                  case 9:
                  case 10:
                  case 0xb:
                  case 0xc:
                  case 0xd:
                  case 0xe:
                  case 0xf:
                  case 0x10:
                  case 0x11:
                  case 0x12:
                  case 0x13:
                  case 0x14:
                  case 0x15:
                  case 0x16:
                  case 0x17:
                  case 0x18:
                  case 0x19:
                  case 0x1a:
                  case 0x1b:
                  case 0x1c:
                  case 0x1d:
                  case 0x1e:
                  case 0x1f:
                  case 0x20:
                  case 0x21:
                  case 0x22:
                  case 0x23:
                  case 0x24:
                  case 0x25:
                  case 0x26:
                  case 0x27:
                  case 0x28:
                  case 0x29:
                  case 0x2a:
                  case 0x2b:
                  case 0x2c:
                  case 0x2d:
                  case 0x2e:
                  case 0x2f:
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
                  case 0x3a:
                  case 0x3b:
                  case 0x3c:
                  case 0x3d:
                  case 0x3e:
                  case 0x3f:
                    bVar14 = local_138[uVar10 * 4];
                    bVar11 = local_138[uVar10 * 4 + 1];
                    bVar12 = local_138[uVar10 * 4 + 2];
                    bVar7 = local_138[uVar10 * 4 + 3];
                    uVar2 = 0;
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
                    uVar2 = 0;
                    bVar12 = (bVar12 + (bVar9 & 3)) - 2;
                    bVar14 = (bVar14 + (bVar9 >> 4 & 3)) - 2;
                    bVar11 = (bVar11 + (bVar9 >> 2 & 3)) - 2;
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
                    bVar9 = bVar9 & 0x3f;
                    uVar2 = iVar13 + 2;
                    bVar11 = (bVar11 + bVar9) - 0x20;
                    bVar14 = bVar14 + ((*(byte *)(param_1 + local_158) >> 4) - 0x28) + bVar9;
                    bVar12 = bVar12 + ((*(byte *)(param_1 + local_158) & 0xf) - 0x28) + bVar9;
                    goto LAB_00102690;
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
                    uVar2 = bVar9 & 0x3f;
                    break;
                  default:
                    bVar14 = *(byte *)(param_1 + local_158);
                    bVar11 = *(byte *)(param_1 + 2 + lVar6);
                    bVar12 = *(byte *)(param_1 + 3 + lVar6);
                    uVar2 = 0;
                    local_158 = (ulong)(iVar13 + 4);
                  }
                }
                uVar10 = (ulong)((uint)bVar7 * 0xb + (uint)bVar12 * 7 +
                                 (uint)bVar11 + (uint)bVar11 * 4 + (uint)bVar14 + (uint)bVar14 * 2 &
                                0x3f);
                local_138[uVar10 * 4] = bVar14;
                local_138[uVar10 * 4 + 1] = bVar11;
                local_138[uVar10 * 4 + 2] = bVar12;
                local_138[uVar10 * 4 + 3] = bVar7;
                iVar13 = (int)local_158;
              }
            }
            else {
              uVar2 = uVar2 - 1;
            }
            *(byte *)((long)pvVar4 + (long)iVar5) = bVar14;
            *(byte *)((long)pvVar4 + (long)iVar5 + 1) = bVar11;
            *(byte *)((long)pvVar4 + (long)(iVar5 + 2)) = bVar12;
            if (uVar8 == 4) {
              *(byte *)((long)pvVar4 + (long)(iVar5 + 3)) = bVar7;
            }
            iVar5 = iVar5 + uVar8;
          } while( true );
        }
      }
    }
  }
  return (void *)0x0;
}




uint qoi_read_32(long param_1,int *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  
  iVar4 = *param_2;
  *param_2 = iVar4 + 1;
  bVar1 = *(byte *)(param_1 + iVar4);
  *param_2 = iVar4 + 2;
  bVar2 = *(byte *)(param_1 + (iVar4 + 1));
  *param_2 = iVar4 + 3;
  bVar3 = *(byte *)(param_1 + (iVar4 + 2));
  *param_2 = iVar4 + 4;
  return (uint)bVar3 << 8 | (uint)bVar2 << 0x10 | (uint)bVar1 << 0x18 |
         (uint)*(byte *)(param_1 + (iVar4 + 3));
}



