// DES.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//密钥置换表1
const static int PCC_Table[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};

//密钥置换表2
const static char PCC2_Table[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

//循环位移表
const static int LOOP_Table[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

//IP置换表
const static int IP_Table[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

//E扩展置换表
const static int Extension_Table[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

//S盒替换表
const static int S_Box[8][4][16] = {
	//S1
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13,
	//S2
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	//S3
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12,
	//S4
	7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14,
	//S5
	2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3,
	//S6
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13,
	//S7
	4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12,
	//S8
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};

//P盒置换表
const int P_Table[32] = {
	16,  7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26,  5, 18, 31, 10,
	2,  8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};

//RIP置换表
const static int RIP_Table[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};

bool K[16][48];

//将字符转化为8位bit
void ByteToBit(bool *T, char *in, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			T[i * 8 + j] = (in[i] & (1 << (7 - j))) ? true : false;
		}
	}
}

//将8位bit转化为字符
void BitToByte(bool *T, char *out, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			int p = T[i * 8 + j] ? 1 : 0;
			out[i] |= p << (7 - j);
		}
	}
}

//初始化密钥表
void SetKey(bool *Key)
{
	memset(K, 0, sizeof(K));

	bool L[56], R[56];

	for (int i = 0; i < 28; i++)
	{
		L[i] = L[i + 28] = Key[PCC_Table[i] - 1];
		R[i] = R[i + 28] = Key[PCC_Table[i + 28] - 1];
	}

	int st = 0;
	for (int i = 0; i < 16; i++)
	{
		st += LOOP_Table[i];
		for (int j = 0; j < 48; j++)
		{
			K[i][j] = (PCC2_Table[j] - 1<28) ? L[PCC2_Table[j] - 1 + st] : R[PCC2_Table[j] - 1 + st - 28];
		}
	}
}

//IP置换
void Initial_Permutation(bool *L, bool *R)
{
	bool tmp[64];
	for (int i = 0; i < 64; i++)
	{
		tmp[i] = (IP_Table[i] - 1)<32 ? L[IP_Table[i] - 1] : R[IP_Table[i] - 33];
	}
	for (int i = 0; i < 32; i++)
	{
		L[i] = tmp[i];
		R[i] = tmp[i + 32];
	}
}

//扩展置换&&异或
void Extension_Permutation(bool *X, bool *T, bool *key)
{
	for (int i = 0; i < 48; i++)
	{
		X[i] = T[Extension_Table[i] - 1] ^ key[i];
	}
}

//S盒代替
void Sbox_Permutation(bool *X, bool *T)
{
	for (int i = 0; i < 8; i++)
	{
		int st = i * 6;
		int a = (X[st] << 1) + X[st + 5];
		int b = (X[st + 1] << 3) + (X[st + 2] << 2) + (X[st + 3] << 1) + (X[st + 4]);
		int tmp = S_Box[i][a][b];
		int st2 = i * 4;
		for (int j = 0; j < 4; j++)
		{
			T[st2 + 3 - j] |= (tmp >> j) & 1;
		}
	}
}

//P盒置换
void Pbox_Permutation(bool *X, bool *T)
{
	for (int i = 0; i < 32; i++)
	{
		T[i] = X[P_Table[i] - 1];
	}
}

//IP逆置换
void Final_Permutation(bool *L, bool *R)
{
	bool tmp[64];
	for (int i = 0; i < 64; i++)
	{
		tmp[i] = (RIP_Table[i] - 1<32) ? L[RIP_Table[i] - 1] : R[RIP_Table[i] - 33];
	}
	for (int i = 0; i < 32; i++)
	{
		L[i] = tmp[i];
		R[i] = tmp[i + 32];
	}
}

//DES加密
void DES_E(char *in, int inlen, char *key, int keylen, char *out)
{
	bool Key[64];
	ByteToBit(Key, key, 8);
	SetKey(Key);
	bool L[32], R[32];
	//每次取8位
	for (int i = 0; i < inlen; i += 8)
	{
		ByteToBit(L, in + i, 4);
		ByteToBit(R, in + i + 4, 4);
		//IP置换
		Initial_Permutation(L, R);
		for (int j = 0; j < 16; j++)
		{
			bool X[48];
			memset(X, 0, sizeof(X));
			//扩展置换 异或运算
			Extension_Permutation(X, R, K[j]);
			bool t[32];
			memset(t, 0, sizeof(t));
			//S盒替换
			Sbox_Permutation(X, t);
			//P盒置换
			Pbox_Permutation(X, t);
			//异或
			for (int k = 0; k < 32; k++)
				L[k] ^= t[k];
			if (j == 15)
				break;
			//交换
			memcpy(t, L, sizeof(L));
			memcpy(L, R, sizeof(R));
			memcpy(R, t, sizeof(t));
		}
		//IP逆置换
		Final_Permutation(L, R);
		BitToByte(L, out + i, 4);
		BitToByte(R, out + i + 4, 4);
	}
}

//DES解密
void DES_D(char *in, int inlen, char *key, int keylen, char *out)
{
	bool L[32], R[32];
	//每次取8位
	for (int i = 0; i < inlen; i += 8)
	{
		ByteToBit(L, in + i, 4);
		ByteToBit(R, in + i + 4, 4);
		//IP置换
		Initial_Permutation(L, R);
		for (int j = 15; j >= 0; j--)
		{
			bool X[48];
			memset(X, 0, sizeof(X));
			//扩展置换 异或运算
			Extension_Permutation(X, R, K[j]);
			bool t[32];
			memset(t, 0, sizeof(t));
			//S盒替换
			Sbox_Permutation(X, t);
			//P盒置换
			Pbox_Permutation(X, t);
			//异或
			for (int k = 0; k < 32; k++)
				L[k] ^= t[k];
			if (j == 0)
				break;
			//交换
			memcpy(t, L, sizeof(L));
			memcpy(L, R, sizeof(R));
			memcpy(R, t, sizeof(t));
		}
		//IP逆置换
		Final_Permutation(L, R);
		BitToByte(L, out + i, 4);
		BitToByte(R, out + i + 4, 4);
	}
}