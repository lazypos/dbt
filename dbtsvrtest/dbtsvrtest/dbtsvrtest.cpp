// dbtsvrtest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <map>
#include <string>
using namespace std;

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

int main()
{
	WSAData data;
	WSAStartup(MAKEWORD(2,2), &data);

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5183);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	SOCKET _s = socket(AF_INET, SOCK_STREAM, 0);
	bind(_s, (struct sockaddr*)&servaddr, sizeof(servaddr));
	listen(_s, 10);
	SOCKET cli = accept(_s, nullptr, nullptr);
	while (true){
		char buf[1024] = { 0 };
		recv(cli, buf, 1024, 0);
		map<string, string> mmm;
		stringToMap(buf, mmm, ";");
		string rst;
		//登陆场景
		if (mmm["cmd"] == "login")
		{
			if (mmm["type"] == "login")//登陆
			{
				if (mmm["user"]=="A123456" && mmm["pass"]=="MTIzNDU2")
				{
					rst = "logntype=login;result=ok";
					int len = rst.length();
					send(cli, (char*)&len, 4, 0);
					send(cli, rst.c_str(), rst.length(),0);
				}
				else {
					rst = "logntype=login;result=error";
					int len = rst.length();
					send(cli, (char*)&len, 4, 0);
					send(cli, rst.c_str(), rst.length(), 0);
				}
			}
			if (mmm["type"] == "regist")//注册
			{
				rst = "logntype=regist;result=用户名已存在！";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
		}
		//大厅
		if (mmm["cmd"] == "hall")
		{
			if (mmm["type"] == "getmsg")//登陆
			{
				rst = "halltype=getmsg;nick=dagouge;score=123123;total=123;win=12.3%";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
			if (mmm["type"] == "find")
			{
				rst = "halltype=adddesk;result=-1";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
			if (mmm["type"] == "add" || mmm["type"] == "create")
			{
				rst = "halltype=adddesk;result=ok";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
		}

	}


	WSACleanup();
    return 0;
}

