// #include "stdafx.h"
// //#include "Global.h"
// #include <string.h>
// 
// std::string readFile(const string& path)
// {
// 	if (path.empty())
// 		return "";
// 	
// 	ostringstream fileContent;
// 	ifstream ifs(path, ios::binary | ios::in);
// 	if (ifs){
// 		fileContent << ifs.rdbuf();
// 		ifs.close();
// 	}
// 	return fileContent.str();
// }
// 
// bool writeFile(const string& path, const string& content)
// {
// 	if (path.empty())
// 		return "";
// 
// 	ofstream ofs(path, ios::binary | ios::out);
// 	if (ofs){
// 		ofs << content;
// 		ofs.close();
// 		return true;
// 	}
// 	return false;
// }
// 
// void stringToMap(const string& src, map<string, string>& m, const string& sep/*="\r\n"*/)
// {
// 	m.clear();
// 	size_t len = sep.length();
// 	if (len == 0 || src.empty())
// 		return;
// 	char* psrc = (char *)src.c_str();
// 	char* sp = (char *)sep.c_str();
// 	char* pitem = strstr(psrc, sp);
// 	char* eq = NULL;
// 	while (pitem != NULL) {
// 		eq = strstr(psrc, "=");
// 		if (eq && eq < pitem) {
// 			m.emplace(string(psrc, eq), string(eq + 1, pitem - eq - 1));
// 		}
// 		psrc = pitem + len;
// 		pitem = strstr(psrc, sp);
// 	}
// 	if (psrc != NULL) {
// 		eq = strstr(psrc, "=");
// 		if (eq)
// 			m.emplace(string(psrc, eq), string(eq + 1));
// 	}
// }
// 
// void stringToList(const string& src, list<string>& lst, const string& sep /*= "\r\n"*/)
// {
// 	lst.clear();
// 	char *psrc = (char*)src.c_str();
// 	char *pend = (char*)src.c_str() + src.length();
// 	char* sp = (char*)sep.c_str();
// 	size_t len = sep.length();
// 
// 	char* pitem = strstr(psrc, sp);
// 	while (pitem != NULL) {
// 		if (pitem > psrc)
// 			lst.emplace_back(string(psrc, pitem));
// 		psrc = pitem + len;
// 		pitem = strstr(psrc, sp);
// 	}
// 	if (psrc != NULL && psrc != pend)
// 		lst.emplace_back(string(psrc));
// }
// 
// void stringToSet(const string& src, set<string>& lst, const string& sep /*= "\r\n"*/)
// {
// 	lst.clear();
// 	char *psrc = (char*)src.c_str();
// 	char *pend = (char*)src.c_str() + src.length();
// 	char* sp = (char*)sep.c_str();
// 	size_t len = sep.length();
// 
// 	char* pitem = strstr(psrc, sp);
// 	while (pitem != NULL) {
// 		if (pitem > psrc)
// 			lst.insert(string(psrc, pitem));
// 		psrc = pitem + len;
// 		pitem = strstr(psrc, sp);
// 	}
// 	if (psrc != NULL && psrc != pend)
// 		lst.insert(string(psrc));
// }
// 
// void myReplace(string& src, const string& s, const string& to)
// {
// 	size_t posbg;
// 	while ((posbg = src.find(s)) != string::npos) {
// 		src.replace(posbg, s.size(), to);
// 	}
// }
// 
// int    zcw_string_repalce_all(const char* src, int srclen,
// 	const char* tofind, int flen,
// 	const char* toplace, int plen,
// 	char **rst, int* rlen)
// {
// 	if (flen > srclen || flen < 1 || plen < 0 || srclen < 1
// 		|| rst == NULL || rlen == NULL || src == NULL
// 		|| tofind == NULL || toplace == NULL)
// 		return -1;
// 	int times = 0;        // recode replace time
// 	int nlen = 0;        // recode result len
// 	int last_pos = 0;    // recode source last position
// 	int pos = 0;
// 	while (pos <= srclen - flen)
// 	{
// 		if (memcmp(src + pos, tofind, flen) == 0)
// 		{
// 			times++;
// 			// realloc result size
// 			*rst = (char*)realloc(*rst, (nlen + pos - last_pos + plen)*sizeof(char));
// 			memset(*rst + nlen, 0, pos - last_pos + plen);
// 			// copy new content to result
// 			memcpy(*rst + nlen, src + last_pos, pos - last_pos);
// 			nlen += pos - last_pos;
// 			memcpy(*rst + nlen, toplace, plen);
// 			nlen += plen;
// 			// update position
// 			pos += flen;
// 			last_pos = pos;
// 		}
// 		else
// 			pos++;
// 	}
// 	// add last string
// 	*rst = (char*)realloc(*rst, (nlen + pos - last_pos + 1)*sizeof(char));
// 	memset(*rst + nlen, 0, pos - last_pos + 1);
// 	memcpy(*rst + nlen, src + last_pos, pos - last_pos);
// 	nlen += pos - last_pos;
// 	// copy the result length
// 	*rlen = nlen;
// 	return times;
// }
// 
// void parseIPRangeToVector(const string& iprange, vector< pair<unsigned long, unsigned long> >& vecLicence)
// {
// 	vecLicence.clear();
// 	if (iprange.empty())
// 		return;
// 
// 	list<string> tmp;
// 	string tmpiprange = iprange;
// 	myReplace(tmpiprange, ",", ";");
// 	stringToList(iprange, tmp, ";");
// 
// 	for (auto it : tmp){
// 		size_t pos = it.find("-");
// 		if (pos == string::npos){
// 			unsigned int dwip = ntohl(inet_addr(it.c_str()));
// 			vecLicence.push_back(make_pair(dwip, dwip));
// 		}
// 		else {
// 			string ipbg = string(it, 0, pos);
// 			unsigned int dwipbg = ntohl(inet_addr(ipbg.c_str()));
// 			string iped = string(it, pos+1);
// 			unsigned int dwiped = ntohl(inet_addr(iped.c_str()));
// 			vecLicence.push_back(make_pair(dwipbg, dwiped));
// 		}
// 	}
// 
// }
// 
// void parseIPRangeToUnOrderdMap(const string& iprange, unordered_map<unsigned long, unsigned long>& mapLicence)
// {
// 	mapLicence.clear();
// 	if (iprange.empty())
// 		return;
// 
// 	list<string> tmp;
// 	string tmpiprange = iprange;
// 	myReplace(tmpiprange, ",", ";");
// 	stringToList(iprange, tmp, ";");
// 
// 	for (auto it : tmp) {
// 		size_t pos = it.find("-");
// 		if (pos == string::npos) {
// 			unsigned int dwip = ntohl(inet_addr(it.c_str()));
// 			mapLicence.emplace(dwip, dwip);
// 		}
// 		else {
// 			string ipbg = string(it, 0, pos);
// 			unsigned int dwipbg = ntohl(inet_addr(ipbg.c_str()));
// 			string iped = string(it, pos + 1);
// 			unsigned int dwiped = ntohl(inet_addr(iped.c_str()));
// 			mapLicence.emplace(dwipbg, dwiped);
// 		}
// 	}
// }
// 
// std::string getpath()
// {
// 	char szpath[1024] = { 0 };
// #ifdef WIN32
// 	DWORD dwLen = GetModuleFileName(NULL, szpath, 1020);
// 	while (dwLen > 0) {
// 		if (szpath[dwLen] == '/' || szpath[dwLen] == '\\') {
// 			szpath[dwLen] = 0;
// 			break;
// 		}
// 		dwLen--;
// 	}
// #endif
// 	return string(szpath);
// }
// 
// std::string getPerPath(const string& path)
// {
// 	if (path.find("/") != string::npos){
// 		size_t pos = path.rfind("/");
// 		return path.substr(0, pos);
// 	}
// 	else {
// 		size_t pos = path.rfind("\\");
// 		return path.substr(0, pos);
// 	}
// }
