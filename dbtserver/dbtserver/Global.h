#ifndef _h_global_h_
#define _h_global_h_
#include "header.h"
//读取文件
string  readFile(const string& path);
//写文件
bool	writeFile(const string& path, const string& content);
//字符串分入map表
void	stringToMap(const string& src, map<string, string>& m, const string& sep="\r\n");
//字符串分入list表
void	stringToList(const string& src, list<string>& lst, const string& sep = "\r\n");
// 字符串分入vector
void	stringToVector(const string& src, vector<string>& lst, const string& sep = "\r\n");
//字符串分入set
void	stringToSet(const string& src, set<string>& lst, const string& sep = "\r\n");
//字符串替换
void	myReplace(string& src, const string& s, const string& to);
//C风格字符串高效替换
int    zcw_string_repalce_all(const char* src, int srclen,
	const char* tofind, int flen,
	const char* toplace, int plen,
	char **rst, int* rlen);

#endif // !