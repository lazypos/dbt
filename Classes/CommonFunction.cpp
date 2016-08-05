#include "CommonFunction.h"


bool checkUserIegal(const string& name)
{
	if (name.length() < 4 || name.length() > 8)
		return false;
	for (size_t i = 0; i < name.size(); ++i) {
		if (!isalpha(name[i]) && !isdigit(name[i]))
			return false;
	}
	return true;
}

bool checkPassIegal(const string& pass)
{
	if (pass.length() < 6 || pass.length() > 12)
		return false;
	for (size_t i = 0; i < pass.size(); ++i) {
		if (!isascii(pass[i]))
			return false;
	}
	return true;
}

bool checkNickIegal(const string& name)
{
	if (name.length() > 10 || name.length() < 4)
		return false;
	if (name.find(".") != string::npos
		|| name.find("'") != string::npos
		|| name.find("\"") != string::npos
		|| name.find("`") != string::npos
		|| name.find("*") != string::npos
		|| name.find("&") != string::npos
		|| name.find("!") != string::npos
		|| name.find("/") != string::npos
		|| name.find("<") != string::npos
		|| name.find(">") != string::npos
		|| name.find("|") != string::npos
		|| name.find("\\") != string::npos)
		return false;
	return true;
}

void stringToMap(const string& src, map<string, string>& m, const string& sep/*="\r\n"*/)
{
	m.clear();
	size_t len = sep.length();
	if (len == 0 || src.empty())
		return;
	char* psrc = (char *)src.c_str();
	char* sp = (char *)sep.c_str();
	char* pitem = strstr(psrc, sp);
	char* eq = NULL;
	while (pitem != NULL) {
		eq = strstr(psrc, "=");
		if (eq && eq < pitem) {
			m.emplace(string(psrc, eq), string(eq + 1, pitem - eq - 1));
		}
		psrc = pitem + len;
		pitem = strstr(psrc, sp);
	}
	if (psrc != NULL) {
		eq = strstr(psrc, "=");
		if (eq)
			m.emplace(string(psrc, eq), string(eq + 1));
	}
}

void stringToList(const string& src, list<string>& lst, const string& sep /*= "\r\n"*/)
{
	lst.clear();
	char *psrc = (char*)src.c_str();
	char *pend = (char*)src.c_str() + src.length();
	char* sp = (char*)sep.c_str();
	size_t len = sep.length();

	char* pitem = strstr(psrc, sp);
	while (pitem != NULL) {
		if (pitem > psrc)
			lst.emplace_back(string(psrc, pitem));
		psrc = pitem + len;
		pitem = strstr(psrc, sp);
	}
	if (psrc != NULL && psrc != pend)
		lst.emplace_back(string(psrc));
}

void stringToVector(const string& src, vector<string>& lst, const string& sep /*= "\r\n"*/)
{
	lst.clear();
	char *psrc = (char*)src.c_str();
	char *pend = (char*)src.c_str() + src.length();
	char* sp = (char*)sep.c_str();
	size_t len = sep.length();

	char* pitem = strstr(psrc, sp);
	while (pitem != NULL) {
		if (pitem > psrc)
			lst.emplace_back(string(psrc, pitem));
		psrc = pitem + len;
		pitem = strstr(psrc, sp);
	}
	if (psrc != NULL && psrc != pend)
		lst.emplace_back(string(psrc));
}
