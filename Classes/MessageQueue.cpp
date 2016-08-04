#include "MessageQueue.h"


CMessageQueue::CMessageQueue()
{
	WSAData data;
	WSAStartup(MAKEWORD(2, 2), &data);
}


CMessageQueue::~CMessageQueue()
{
	WSACleanup();
}

bool CMessageQueue::start()
{
	memset(&_servAddr, 0, sizeof(_servAddr));
	_servAddr.sin_family = AF_INET;
	_servAddr.sin_port = htons(5183);
	_servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock == 0)
		return false;
	if (connect(_sock, (struct sockaddr*)&_servAddr, sizeof(_servAddr)))
		return false;

	_threadPrt = make_shared<thread>(bind(&CMessageQueue::threadWork, this));
	_threadPrt->detach();
	return true;
}

bool CMessageQueue::sendMessage(const string& str)
{
	size_t len = 0;
	while (len < str.length()) {
		int n = send(_sock, str.c_str() + len, str.length() - len, 0);
		if (n <= 0){
			MessageBox("与服务器断开连接!","error");
			return false;
		}
		len += n;
	}
	return true;
}

bool CMessageQueue::recvMessage(string& text)
{
	size_t len = 0;
	int n = recv(_sock, (char*)&len, 4, 0);
	if (n != 4 || len < 0) {
		MessageBox("从服务器接收数据错误.", "error");
		return false;
	}
	size_t recvlen = 0;
	text.resize(len, 0);
	while (recvlen < len){
		n = recv(_sock, (char*)(text.c_str() + recvlen), len - recvlen, 0);
		if (n <= 0){
			MessageBox("与服务器断开连接!", "error");
			return false;
		}
		recvlen += n;
	}
	return true;
}

bool CMessageQueue::sendAndRecv(const string& strSend, string& strRecv)
{
	if (sendMessage(strSend))
		return recvMessage(strRecv);
	return false;
}

void CMessageQueue::threadWork()
{
	while (true){
		string str;
		if (!recvMessage(str))
			break;
		__NotificationCenter::getInstance()->postNotification(str.substr(0,4), __String::create(str.substr(4)));
	}
}
