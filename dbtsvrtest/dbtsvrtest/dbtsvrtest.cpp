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
		//桌子
		if (mmm["cmd"]=="desk")
		{
#define delay_time 1
			if (mmm["type"] == "getmsg")//获取信息
			{	//player=id<>nick<>score<>tatol<>win<>ready|。。
				//当时的信息 0,1,3
				rst = "desktype=getmsg;desknum=78;id=1;player=0<>cbs<>2300<>12<>80%<>1|1<>1dsa<>111<>123<>60%<>0|3<>cjl<>1200<>324<>30%<>0";
				int len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//3准备
				rst = "desktype=play;state=ready;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//2加入
				rst = "desktype=play;state=add;player=2<>cdad<>120<>3222<>22%<>0";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//3离开
				rst = "desktype=play;state=leave;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//2准备
				rst = "desktype=play;state=ready;id=2";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//3加入
				rst = "desktype=play;state=add;player=3<>cbd<>120<>3222<>20%<>0";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(delay_time);
				//3准备
				rst = "desktype=play;state=ready;id=3";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(5000);
				//开始
				rst = "desktype=play;state=start;now=1;cards=1,1,3,4,5,6,12,12,34,34,4,42,42,32,12,23,4,6,7,32,25,23,23,21,23,53,45,45,45,6,32,53,15,32,38,40,29,29,28,39,38";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(2000);

				//出牌
				rst = "desktype=play;state=put;per=1;now=2;cards=23,23,23;surplus=30";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(2000);
				//出牌
				rst = "desktype=play;state=put;per=2;now=3;cards=23,23,23;surplus=30";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(2000);
				//出牌
				rst = "desktype=play;state=put;per=3;now=0;cards=;surplus=30;clear=1";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(2000);
				//出牌
				rst = "desktype=play;state=put;per=0;now=-1;cards=23,23,23;surplus=0;go=1";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//得分
				rst = "desktype=play;state=score;0=120;1=230";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				//结束
				rst = "desktype=play;state=over;n0=dsad;n1=dsad;n2=player3;n3=dsads;s0=20;s1=-20;s2=20;s3=-20";
				len = rst.length();
				send(cli, (char*)&len, 4, 0);
				send(cli, rst.c_str(), rst.length(), 0);
				Sleep(2000);
			}
		}
	}


	WSACleanup();
    return 0;
}

