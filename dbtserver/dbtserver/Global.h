#ifndef _h_global_h_
#define _h_global_h_
#include "header.h"
//��ȡ�ļ�
string  readFile(const string& path);
//д�ļ�
bool	writeFile(const string& path, const string& content);
//�ַ�������map��
void	stringToMap(const string& src, map<string, string>& m, const string& sep="\r\n");
//�ַ�������list��
void	stringToList(const string& src, list<string>& lst, const string& sep = "\r\n");
// �ַ�������vector
void	stringToVector(const string& src, vector<string>& lst, const string& sep = "\r\n");
//�ַ�������set
void	stringToSet(const string& src, set<string>& lst, const string& sep = "\r\n");
//�ַ����滻
void	myReplace(string& src, const string& s, const string& to);
//C����ַ�����Ч�滻
int    zcw_string_repalce_all(const char* src, int srclen,
	const char* tofind, int flen,
	const char* toplace, int plen,
	char **rst, int* rlen);

#endif // !