#include "stdafx.h"
#include "des.h"
using namespace std;

int main(void)
{
	char key[20];
	printf("Pleasr input the key(16 character)\n");
	cin >> key;
	char text[1000];
	char encrypt_text[1000];
	char decrypt_text[1000];

	memset(encrypt_text, 0, sizeof(encrypt_text));
	memset(decrypt_text, 0, sizeof(decrypt_text));
	printf("Pleasr input the Text\n");
	cin >> text;

	DES_E(text, strlen(text), key, 8, encrypt_text);
	printf("%s\n", encrypt_text);

	DES_D(encrypt_text, strlen(encrypt_text), key, 8, decrypt_text);

	printf("%s\n", decrypt_text);

	/*
	bool tex[1000];
	ByteToBit(tex, text, strlen(text));
	for (int i = 0; i < 8 * strlen(text); i++)
	printf("%d", tex[i] ? 1 : 0);
	cout << endl;

	bool encrypt[1000];
	ByteToBit(encrypt, encrypt_text, strlen(encrypt_text));
	for (int i = 0; i < 8 * strlen(encrypt_text); i++)
	printf("%d", encrypt[i] ? 1 : 0);
	cout << endl;

	bool decrypt[1000];
	ByteToBit(decrypt, decrypt_text, strlen(decrypt_text));
	for (int i = 0; i < 8 * strlen(decrypt_text); i++)
	printf("%d", decrypt[i] ? 1 : 0);
	cout << endl;
	*/

	system("pause");
	return 0;
}
