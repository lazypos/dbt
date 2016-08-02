#ifndef _CMessageQueue_h_
#define _CMessageQueue_h_

#include <memory>
#include <thread>
#include "cocos2d.h"
#include "Singleton.h"
using namespace std;
USING_NS_CC;

class CMessageQueue
{
public:
	CMessageQueue();
	~CMessageQueue();

	bool	start();
	bool	sendMessage(const string& str);
	bool	recvMessage(string& text);
	bool	sendAndRecv(const string& strSend, string& strRecv);
private:
	void	threadWork();

	shared_ptr<thread> _threadPrt;
	
	SOCKET	_sock;
	struct  sockaddr_in _servAddr;
};

typedef CSingleton<CMessageQueue>	messageQueue;

#endif 