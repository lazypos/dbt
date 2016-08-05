// dbtsvrtest.cpp : �������̨Ӧ�ó������ڵ㡣
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
		//��½����
		if (mmm["cmd"] == "login")
		{
			if (mmm["type"] == "login")//��½
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
			if (mmm["type"] == "regist")//ע��
			{
				rst = "logntype=regist;result=�û����Ѵ��ڣ�";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
		}
		//����
		if (mmm["cmd"] == "hall")
		{
			if (mmm["type"] == "getmsg")//��½
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
		//����
		if (mmm["cmd"]=="desk")
		{
			if (mmm["type"] == "getmsg")//��ȡ��Ϣ
			{	//player=id<>nick<>score<>tatol<>win<>ready|����
				//��ʱ����Ϣ 0,1,3
				rst = "desktype=getmsg;desknum=78;id=1;player=0<>cbs<>2300<>12<>80%<>1|3<>cjl<>1200<>324<>30%<>0";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//3׼��
				rst = "desktype=play;state=ready;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//2����
				rst = "desktype=play;state=add;player=2<>cdad<>120<>3222<>22%<>0";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//3�뿪
				rst = "desktype=play;state=leave;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//2׼��
				rst = "desktype=play;state=ready;id=2";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//3����
				rst = "desktype=play;state=add;player=3<>cbd<>120<>3222<>20%<>0";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//3׼��
				rst = "desktype=play;state=ready;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
			}
		}
	}


	WSACleanup();
    return 0;
}

