#pragma once
#include "stdafx.h"

//���ַ�ת��Ϊ8λbit
void ByteToBit(bool *T, char *in, int len);

//��8λbitת��Ϊ�ַ�
void BitToByte(bool *T, char *out, int len);

//��ʼ����Կ��
void SetKey(bool *Key);

//IP�û�
void Initial_Permutation(bool *L, bool *R);

//��չ�û�&&���
void Extension_Permutation(bool *X, bool *T, bool *key);

//S�д���
void Sbox_Permutation(bool *X, bool *T);

//P���û�
void Pbox_Permutation(bool *X, bool *T);

//IP���û�
void Final_Permutation(bool *L, bool *R);

//DES����
void DES_E(char *in, int inlen, char *key, int keylen, char *out);

//DES����
void DES_D(char *in, int inlen, char *key, int keylen, char *out);
