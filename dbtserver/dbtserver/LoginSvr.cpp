#include "LoginSvr.h"
#include "Config.h"

CLoginSvr::CLoginSvr()
{
}


CLoginSvr::~CLoginSvr()
{
}

bool CLoginSvr::start(uint16_t port)
{
	struct sockaddr_in serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(port);

	_eventbase = event_base_new();
	if (!_eventbase) {
		LERROR << "event_base_new error.";
		return false;
	}

	_listener = evconnlistener_new_bind(_eventbase, listener_cb, this,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
		-1, (struct sockaddr*)&serv, sizeof(serv));
	if (_listener == NULL) {
		LERROR << "evconnlistener_new_bind false.";
		return false;
	}
	return true;
}

void CLoginSvr::run()
{
	if (_eventbase == nullptr || _listener == nullptr)
		return;

	event_base_dispatch(_eventbase);
	evconnlistener_free(_listener);
	event_base_free(_eventbase);
}

void CLoginSvr::stop()
{
	event_base_loopexit(_eventbase, nullptr);
}

void CLoginSvr::listener_cb(struct evconnlistener* listener, evutil_socket_t fd,
			struct sockaddr *adddr, int socklen, void *p)
{
	struct sockaddr_in *remoteAddr = (struct sockaddr_in*)adddr;
	char buf[20] = { 0 };
	LDEBUG << "Recv remote ip:" << evutil_inet_ntop(AF_INET, reinterpret_cast<void*>(&remoteAddr->sin_addr), buf, 16);
	// 设置为非阻塞
	if (evutil_make_socket_nonblocking(fd) < 0) {
		LERROR << "evutil_make_socket_nonblocking false.";
		evutil_closesocket(fd);
		return;
	}
	// 新建连接类
	if (!configMgr::Instance()->isExit()){
		CLoginSvr* server = static_cast<CLoginSvr*>(p);
		conn_ptr conn = std::make_shared<CConnect>();
		conn->initConnect(server->_eventbase, fd, buf);

		server->_mapConnected.emplace(conn, 0);
		LINFO << "当起已有连接数:" << server->_mapConnected.size();
	}
}
