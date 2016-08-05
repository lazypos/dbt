#ifndef _CCommonFunction_h_
#define _CCommonFunction_h_
#include <string>
#include <map>
#include <list>
#include <vector>
using namespace std;

#define  MOD 18
int inline encrypt_v2(const unsigned char *src, unsigned char *dec, int len)
{
	if (!src || !dec || len < 0 || src == dec)
		return -1;

	for (int i = 0, j = MOD; i < len; i++, j++)
	{
		j %= MOD + 1;
		*(dec + i) = (((*(src + i)) & 0xf0) >> 4) + (((*(src + i)) & 0x0f) << 4);
		*(dec + i) = (((*(dec + i)) + j) % MOD) ^ (j & 0xff);
	}

	return 0;
}

int inline decrypt_v2(const unsigned char *src, unsigned char *dec, int len)
{
	if (!src || !dec || len < 0 || src == dec)
		return -1;

	for (int i = 0, j = MOD; i < len; i++, j++)
	{
		j %= MOD + 1;
		*(dec + i) = ((*(src + i) ^ (j & 0xff)) + MOD - j) % MOD;
		*(dec + i) = (((*(dec + i)) & 0xf0) >> 4) + (((*(dec + i)) & 0x0f) << 4);
	}
	return 0;
}

bool checkUserIegal(const string& name);
bool checkPassIegal(const string& pass);
bool checkNickIegal(const string& name);


void stringToMap(const string& src, map<string, string>& m, const string& sep/*="\r\n"*/);
void stringToList(const string& src, list<string>& lst, const string& sep /*= "\r\n"*/);
void stringToVector(const string& src, vector<string>& lst, const string& sep /*= "\r\n"*/);
#endif

