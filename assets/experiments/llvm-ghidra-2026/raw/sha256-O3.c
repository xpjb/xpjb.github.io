
void sha256_transform(long param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint local_138 [66];
  
  uVar1 = *param_2;
  local_138[0] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[1];
  local_138[1] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[2];
  local_138[2] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[3];
  local_138[3] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[4];
  local_138[4] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[5];
  local_138[5] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[6];
  local_138[6] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[7];
  local_138[7] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[8];
  local_138[8] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[9];
  local_138[9] = CONCAT13((char)uVar1,
                          CONCAT12((char)((uint)uVar1 >> 8),
                                   CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))
                                  ));
  uVar1 = param_2[10];
  local_138[10] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  uVar1 = param_2[0xb];
  local_138[0xb] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  uVar1 = param_2[0xc];
  local_138[0xc] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  uVar1 = param_2[0xd];
  local_138[0xd] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  uVar1 = param_2[0xe];
  local_138[0xe] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  uVar1 = param_2[0xf];
  local_138[0xf] =
       CONCAT13((char)uVar1,
                CONCAT12((char)((uint)uVar1 >> 8),
                         CONCAT11((char)((uint)uVar1 >> 0x10),(char)((uint)uVar1 >> 0x18))));
  lVar4 = 0;
  do {
    uVar3 = local_138[lVar4 + 0xe];
    uVar7 = local_138[lVar4 + 1];
    uVar15 = local_138[lVar4 + 2];
    uVar5 = (uVar3 >> 10 ^ (uVar3 >> 0x13 | uVar3 << 0xd) ^ (uVar3 >> 0x11 | uVar3 << 0xf)) +
            local_138[lVar4 + 9] + local_138[lVar4] +
            (uVar7 >> 3 ^ (uVar7 >> 0x12 | uVar7 << 0xe) ^ (uVar7 >> 7 | uVar7 << 0x19));
    local_138[lVar4 + 0x10] = uVar5;
    uVar3 = local_138[lVar4 + 0xf];
    uVar9 = (uVar15 >> 3 ^ (uVar15 >> 0x12 | uVar15 << 0xe) ^ (uVar15 >> 7 | uVar15 << 0x19)) +
            uVar7 + (uVar3 >> 10 ^ (uVar3 >> 0x13 | uVar3 << 0xd) ^ (uVar3 >> 0x11 | uVar3 << 0xf))
                    + local_138[lVar4 + 10];
    local_138[lVar4 + 0x11] = uVar9;
    uVar3 = local_138[lVar4 + 3];
    local_138[lVar4 + 0x12] =
         (uVar3 >> 3 ^ (uVar3 >> 0x12 | uVar3 << 0xe) ^ (uVar3 >> 7 | uVar3 << 0x19)) + uVar15 +
         (uVar5 >> 10 ^ (uVar5 >> 0x13 | uVar5 * 0x2000) ^ (uVar5 >> 0x11 | uVar5 * 0x8000)) +
         local_138[lVar4 + 0xb];
    uVar7 = local_138[lVar4 + 4];
    local_138[lVar4 + 0x13] =
         (uVar7 >> 3 ^ (uVar7 >> 0x12 | uVar7 << 0xe) ^ (uVar7 >> 7 | uVar7 << 0x19)) + uVar3 +
         (uVar9 >> 10 ^ (uVar9 >> 0x13 | uVar9 * 0x2000) ^ (uVar9 >> 0x11 | uVar9 * 0x8000)) +
         local_138[lVar4 + 0xc];
    lVar4 = lVar4 + 4;
  } while (lVar4 != 0x30);
  lVar4 = 0;
  uVar3 = *(uint *)(param_1 + 0x50);
  uVar7 = *(uint *)(param_1 + 0x54);
  uVar15 = *(uint *)(param_1 + 0x58);
  uVar5 = *(uint *)(param_1 + 0x5c);
  uVar9 = *(uint *)(param_1 + 0x60);
  uVar12 = *(uint *)(param_1 + 100);
  uVar10 = *(uint *)(param_1 + 0x68);
  uVar8 = *(uint *)(param_1 + 0x6c);
  do {
    uVar11 = uVar12;
    uVar14 = uVar9;
    uVar6 = uVar7;
    uVar2 = uVar3;
    iVar13 = (~uVar14 & uVar10 | uVar11 & uVar14) + uVar8 +
             ((uVar14 >> 0x19 | uVar14 << 7) ^
             (uVar14 >> 0xb | uVar14 << 0x15) ^ (uVar14 >> 6 | uVar14 << 0x1a)) + (&k)[lVar4] +
             local_138[lVar4];
    uVar12 = uVar5 + iVar13;
    uVar7 = (uVar6 & uVar15 ^ (uVar6 ^ uVar15) & uVar2) +
            ((uVar2 >> 0x16 | uVar2 << 10) ^
            (uVar2 >> 0xd | uVar2 << 0x13) ^ (uVar2 >> 2 | uVar2 << 0x1e)) + iVar13;
    iVar13 = (~uVar12 & uVar11 | uVar14 & uVar12) + uVar10 +
             ((uVar12 >> 0x19 | uVar12 * 0x80) ^
             (uVar12 >> 0xb | uVar12 * 0x200000) ^ (uVar12 >> 6 | uVar12 * 0x4000000)) +
             (&DAT_00100a04)[lVar4] + local_138[lVar4 + 1];
    lVar4 = lVar4 + 2;
    uVar9 = uVar15 + iVar13;
    uVar3 = (uVar2 & uVar6 ^ (uVar2 ^ uVar6) & uVar7) +
            ((uVar7 >> 0x16 | uVar7 * 0x400) ^
            (uVar7 >> 0xd | uVar7 * 0x80000) ^ (uVar7 >> 2 | uVar7 * 0x40000000)) + iVar13;
    uVar15 = uVar2;
    uVar5 = uVar6;
    uVar10 = uVar14;
    uVar8 = uVar11;
  } while (lVar4 != 0x40);
  *(uint *)(param_1 + 0x50) = uVar3 + *(int *)(param_1 + 0x50);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x54);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x5c);
  *(uint *)(param_1 + 0x60) = uVar9 + *(int *)(param_1 + 0x60);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x6c);
  return;
}




void sha256_init(long param_1)

{
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0xbb67ae856a09e667;
  *(undefined8 *)(param_1 + 0x58) = 0xa54ff53a3c6ef372;
  *(undefined8 *)(param_1 + 0x60) = 0x9b05688c510e527f;
  *(undefined8 *)(param_1 + 0x68) = 0x5be0cd191f83d9ab;
  return;
}




void sha256_update(long param_1,long param_2,ulong param_3)

{
  bool bVar1;
  uint uVar2;
  ulong uVar3;
  ulong uVar4;
  
  if (param_3 != 0) {
    uVar2 = *(uint *)(param_1 + 0x40);
    uVar3 = 0;
    uVar4 = 1;
    do {
      *(undefined1 *)(param_1 + (ulong)uVar2) = *(undefined1 *)(param_2 + uVar3);
      uVar2 = *(int *)(param_1 + 0x40) + 1;
      *(uint *)(param_1 + 0x40) = uVar2;
      if (uVar2 == 0x40) {
        sha256_transform(param_1,param_1);
        *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x48) + 0x200;
        uVar2 = 0;
        *(undefined4 *)(param_1 + 0x40) = 0;
      }
      bVar1 = uVar4 < param_3;
      uVar3 = uVar4;
      uVar4 = (ulong)((int)uVar4 + 1);
    } while (bVar1);
  }
  return;
}




void sha256_final(undefined1 (*param_1) [32],undefined1 *param_2)

{
  uint uVar1;
  ulong uVar2;
  long lVar3;
  
  uVar1 = *(uint *)param_1[2];
  uVar2 = (ulong)uVar1;
  (*param_1)[uVar2] = 0x80;
  if (uVar2 < 0x38) {
    if (uVar1 != 0x37) {
      memset(*param_1 + uVar2 + 1,0,0x37 - uVar2);
    }
  }
  else {
    if (uVar1 + 1 < 0x40) {
      memset(*param_1 + (uVar1 + 1),0,(ulong)(0x3e - uVar1) + 1);
    }
    sha256_transform(param_1,param_1);
    *(undefined1 (*) [32])(*param_1 + 0x18) = ZEXT1232(ZEXT812(0));
    *param_1 = ZEXT1232(ZEXT812(0));
  }
  lVar3 = (ulong)(uint)(*(int *)param_1[2] << 3) + *(long *)(param_1[2] + 8);
  *(long *)(param_1[2] + 8) = lVar3;
  param_1[1][0x1f] = (char)lVar3;
  param_1[1][0x1e] = (char)((ulong)lVar3 >> 8);
  param_1[1][0x1d] = (char)((ulong)lVar3 >> 0x10);
  param_1[1][0x1c] = (char)((ulong)lVar3 >> 0x18);
  param_1[1][0x1b] = (char)((ulong)lVar3 >> 0x20);
  param_1[1][0x1a] = (char)((ulong)lVar3 >> 0x28);
  param_1[1][0x19] = (char)((ulong)lVar3 >> 0x30);
  param_1[1][0x18] = (char)((ulong)lVar3 >> 0x38);
  sha256_transform(param_1,param_1);
  *param_2 = param_1[2][0x13];
  param_2[4] = param_1[2][0x17];
  param_2[8] = param_1[2][0x1b];
  param_2[0xc] = param_1[2][0x1f];
  param_2[0x10] = param_1[3][3];
  param_2[0x14] = param_1[3][7];
  param_2[0x18] = param_1[3][0xb];
  param_2[0x1c] = param_1[3][0xf];
  param_2[1] = param_1[2][0x12];
  param_2[5] = param_1[2][0x16];
  param_2[9] = param_1[2][0x1a];
  param_2[0xd] = param_1[2][0x1e];
  param_2[0x11] = param_1[3][2];
  param_2[0x15] = param_1[3][6];
  param_2[0x19] = param_1[3][10];
  param_2[0x1d] = param_1[3][0xe];
  param_2[2] = param_1[2][0x11];
  param_2[6] = param_1[2][0x15];
  param_2[10] = param_1[2][0x19];
  param_2[0xe] = param_1[2][0x1d];
  param_2[0x12] = param_1[3][1];
  param_2[0x16] = param_1[3][5];
  param_2[0x1a] = param_1[3][9];
  param_2[0x1e] = param_1[3][0xd];
  param_2[3] = param_1[2][0x10];
  param_2[7] = param_1[2][0x14];
  param_2[0xb] = param_1[2][0x18];
  param_2[0xf] = param_1[2][0x1c];
  param_2[0x13] = param_1[3][0];
  param_2[0x17] = param_1[3][4];
  param_2[0x1b] = param_1[3][8];
  param_2[0x1f] = param_1[3][0xc];
  return;
}



