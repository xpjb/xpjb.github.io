
void sha256_transform(long param_1,long param_2)

{
  undefined1 auVar1 [32];
  undefined4 uVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [32];
  undefined1 auVar5 [32];
  undefined1 auVar6 [16];
  long lVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint auStack_148 [9];
  int aiStack_124 [5];
  uint auStack_110 [68];
  
  for (lVar7 = 0; lVar7 != 0x10; lVar7 = lVar7 + 1) {
    uVar2 = *(undefined4 *)(param_2 + lVar7 * 4);
    auStack_110[lVar7 + 2] =
         CONCAT13((char)uVar2,
                  CONCAT12((char)((uint)uVar2 >> 8),
                           CONCAT11((char)((uint)uVar2 >> 0x10),(char)((uint)uVar2 >> 0x18))));
  }
  for (lVar7 = 0x10; lVar7 != 0x40; lVar7 = lVar7 + 1) {
    uVar9 = auStack_110[lVar7];
    uVar10 = auStack_148[lVar7 + 1];
    auStack_110[lVar7 + 2] =
         (uVar9 >> 10 ^ (uVar9 >> 0x13 | uVar9 << 0xd) ^ (uVar9 >> 0x11 | uVar9 << 0xf)) +
         aiStack_124[lVar7] + auStack_148[lVar7] +
         (uVar10 >> 3 ^ (uVar10 >> 0x12 | uVar10 << 0xe) ^ (uVar10 >> 7 | uVar10 << 0x19));
  }
  auVar1 = *(undefined1 (*) [32])(param_1 + 0x50);
  lVar7 = 0;
  auVar5 = auVar1;
  while( true ) {
    uVar9 = auVar5._0_4_;
    uVar10 = auVar5._4_4_;
    uVar11 = auVar5._8_4_;
    uVar12 = auVar5._16_4_;
    if (lVar7 == 0x100) break;
    auVar3 = vpshufd_avx(auVar5._0_16_,0xff);
    iVar8 = (~uVar12 & auVar5._24_4_ | auVar5._20_4_ & uVar12) + auVar5._28_4_ +
            ((uVar12 >> 0x19 | uVar12 << 7) ^
            (uVar12 >> 0xb | uVar12 << 0x15) ^ (uVar12 >> 6 | uVar12 << 0x1a)) +
            *(int *)((long)&k + lVar7) + *(int *)((long)auStack_110 + lVar7 + 8);
    lVar7 = lVar7 + 4;
    auVar4 = vpshufd_avx2(auVar5,0x90);
    auVar6 = ZEXT116(0) * auVar3 |
             ZEXT116(1) *
             ZEXT416((uVar10 & uVar11 ^ (uVar10 ^ uVar11) & uVar9) +
                     ((uVar9 >> 0x16 | uVar9 << 10) ^
                     (uVar9 >> 0xd | uVar9 << 0x13) ^ (uVar9 >> 2 | uVar9 << 0x1e)));
    auVar3 = ZEXT116(1) * auVar3;
    auVar5._0_4_ = iVar8 + auVar6._0_4_;
    auVar5._4_4_ = iVar8 + auVar6._4_4_;
    auVar5._8_4_ = iVar8 + auVar6._8_4_;
    auVar5._12_4_ = iVar8 + auVar6._12_4_;
    auVar5._16_4_ = iVar8 + auVar3._0_4_;
    auVar5._20_4_ = iVar8 + auVar3._4_4_;
    auVar5._24_4_ = iVar8 + auVar3._8_4_;
    auVar5._28_4_ = iVar8 + auVar3._12_4_;
    auVar5 = vpblendd_avx2(auVar4,auVar5,0x11);
  }
  *(uint *)(param_1 + 0x50) = uVar9 + auVar1._0_4_;
  *(uint *)(param_1 + 0x54) = uVar10 + auVar1._4_4_;
  *(uint *)(param_1 + 0x58) = uVar11 + auVar1._8_4_;
  *(int *)(param_1 + 0x5c) = auVar5._12_4_ + auVar1._12_4_;
  *(uint *)(param_1 + 0x60) = uVar12 + auVar1._16_4_;
  *(uint *)(param_1 + 100) = auVar5._20_4_ + auVar1._20_4_;
  *(uint *)(param_1 + 0x68) = auVar5._24_4_ + auVar1._24_4_;
  *(int *)(param_1 + 0x6c) = auVar5._28_4_ + auVar1._28_4_;
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
  int iVar1;
  uint uVar2;
  
  for (uVar2 = 0; uVar2 < param_3; uVar2 = uVar2 + 1) {
    *(undefined1 *)(param_1 + (ulong)*(uint *)(param_1 + 0x40)) =
         *(undefined1 *)(param_2 + (ulong)uVar2);
    iVar1 = *(int *)(param_1 + 0x40) + 1;
    *(int *)(param_1 + 0x40) = iVar1;
    if (iVar1 == 0x40) {
      sha256_transform(param_1,param_1);
      *(long *)(param_1 + 0x48) = *(long *)(param_1 + 0x48) + 0x200;
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  return;
}




void sha256_final(undefined1 (*param_1) [32],long param_2)

{
  uint uVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;
  
  uVar2 = *(uint *)param_1[2];
  uVar3 = (ulong)uVar2;
  (*param_1)[uVar3] = 0x80;
  if (uVar3 < 0x38) {
    for (; uVar3 != 0x37; uVar3 = uVar3 + 1) {
      (*param_1)[uVar3 + 1] = 0;
    }
  }
  else {
    for (uVar3 = (ulong)(uVar2 + 1); (uint)uVar3 < 0x40; uVar3 = uVar3 + 1) {
      (*param_1)[uVar3] = 0;
    }
    sha256_transform(param_1,param_1);
    *(undefined1 (*) [32])(*param_1 + 0x18) = ZEXT1232(ZEXT812(0));
    *param_1 = ZEXT1232(ZEXT812(0));
  }
  lVar4 = (ulong)(uint)(*(int *)param_1[2] << 3) + *(long *)(param_1[2] + 8);
  *(long *)(param_1[2] + 8) = lVar4;
  param_1[1][0x1f] = (char)lVar4;
  param_1[1][0x1e] = (char)((ulong)lVar4 >> 8);
  param_1[1][0x1d] = (char)((ulong)lVar4 >> 0x10);
  param_1[1][0x1c] = (char)((ulong)lVar4 >> 0x18);
  param_1[1][0x1b] = (char)((ulong)lVar4 >> 0x20);
  param_1[1][0x1a] = (char)((ulong)lVar4 >> 0x28);
  param_1[1][0x19] = (char)((ulong)lVar4 >> 0x30);
  param_1[1][0x18] = (char)((ulong)lVar4 >> 0x38);
  sha256_transform(param_1,param_1);
  uVar2 = 0x18;
  for (lVar4 = -4; lVar4 != 0; lVar4 = lVar4 + 1) {
    *(char *)(param_2 + 4 + lVar4) = (char)(*(uint *)(param_1[2] + 0x10) >> (uVar2 & 0x1f));
    *(char *)(param_2 + 8 + lVar4) = (char)(*(uint *)(param_1[2] + 0x14) >> (uVar2 & 0x1f));
    *(char *)(param_2 + 0xc + lVar4) = (char)(*(uint *)(param_1[2] + 0x18) >> (uVar2 & 0x1f));
    *(char *)(param_2 + 0x10 + lVar4) = (char)(*(uint *)(param_1[2] + 0x1c) >> (uVar2 & 0x1f));
    *(char *)(param_2 + 0x14 + lVar4) = (char)(*(uint *)param_1[3] >> (uVar2 & 0x1f));
    *(char *)(param_2 + 0x18 + lVar4) = (char)(*(uint *)(param_1[3] + 4) >> (uVar2 & 0x1f));
    *(char *)(param_2 + 0x1c + lVar4) = (char)(*(uint *)(param_1[3] + 8) >> (uVar2 & 0x1f));
    uVar1 = uVar2 & 0x1f;
    uVar2 = uVar2 - 8;
    *(char *)(param_2 + 0x20 + lVar4) = (char)(*(uint *)(param_1[3] + 0xc) >> uVar1);
  }
  return;
}



