#pragma once
#include "stdafx.h"

//将字符转化为8位bit
void ByteToBit(bool *T, char *in, int len);

//将8位bit转化为字符
void BitToByte(bool *T, char *out, int len);

//初始化密钥表
void SetKey(bool *Key);

//IP置换
void Initial_Permutation(bool *L, bool *R);

//扩展置换&&异或
void Extension_Permutation(bool *X, bool *T, bool *key);

//S盒代替
void Sbox_Permutation(bool *X, bool *T);

//P盒置换
void Pbox_Permutation(bool *X, bool *T);

//IP逆置换
void Final_Permutation(bool *L, bool *R);

//DES加密
void DES_E(char *in, int inlen, char *key, int keylen, char *out);

//DES解密
void DES_D(char *in, int inlen, char *key, int keylen, char *out);
