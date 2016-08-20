#ifndef _h_CLoginSvr_h_
#define _h_CLoginSvr_h_
#include "header.h"
#include "Connect.h"
#include "common.h"

class CLoginSvr
{
public:
	CLoginSvr();
	~CLoginSvr();

	bool	start(uint16_t port);
	void	run();
	void	stop();

protected:
	static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr *adddr, int socklen, void *p);

private:
	struct event_base*		_eventbase;
	struct evconnlistener*	_listener;
	std::map<conn_ptr, int> _mapConnected;
};

typedef CMySingleton<CLoginSvr> loginSvr;

#endif
