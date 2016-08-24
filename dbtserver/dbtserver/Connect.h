#ifndef _h_CConnect_h_
#define _h_CConnect_h_
#include "header.h"
#include "Player.h"

class CConnect;
typedef shared_ptr<CConnect> conn_ptr;

class CConnect
	: public CPlayer
	, public enable_shared_from_this<CConnect>
{
public:
	CConnect();
	~CConnect();

	bool	initConnect(struct event_base* ev, evutil_socket_t fd, const string& ip);
	void	closeConnect();
	void	replay(const string& context);

	void	dispath(const string& context);
	inline string	getRemoteIP() const { return _remoteIp; }

protected:
	void	processLogin();
	void	processHall();
	void	processDesk();
	void	processOther();

	void	broadAddDesk();
	void	broadLeaveDesk();
	void	broadReady();

	//deskµÄ
	void	processGetmsg();
	void	processPutCards();
	void	processNoPutCards();

	bool	isGameOver();

private:
	evutil_socket_t		_fd;
	uint32_t			_remotedwIp;
	string				_remoteIp;
	struct bufferevent* _evbuffer;
	struct event_base*  _evbase;
	map<string, string> _mapRecv;
	bool				_bLogin = false;
};

#endif
