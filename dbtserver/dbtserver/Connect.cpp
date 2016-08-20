#include "Connect.h"
#include "delegate.h"
#include "Global.h"
#include "Player.h"
#include "DBManager.h"

CConnect::CConnect()
{
}


CConnect::~CConnect()
{
}

bool CConnect::initConnect(struct event_base* ev, evutil_socket_t fd, const string& ip)
{
	_evbase = ev; _fd = fd; _remoteIp = ip;
	// 新建数据缓存
	_evbuffer = bufferevent_socket_new(_evbase, _fd, BEV_OPT_CLOSE_ON_FREE);
	if (_evbuffer == nullptr) {
		LERROR << "Connect init false. bufferevent_socket_new false." << ip;
		return false;
	}
	// 设置回调，使能读写
	bufferevent_setcb(_evbuffer, read_cb, nullptr, event_cb, (void*)this);
	if (bufferevent_enable(_evbuffer, EV_READ | EV_WRITE) < 0) {
		LERROR << "bufferevent_enable false." << ip;
		return false;
	}
	return true;
}

void CConnect::closeConnect()
{
	evutil_closesocket(_fd);
	if (_evbuffer) {
		bufferevent_free(_evbuffer);
		_evbuffer = nullptr;
	}
}

void CConnect::replay(const string& context)
{
	char len = char(context.length());
	string strReply(def_header_len, 0);
	memcpy((char*)strReply.c_str(), &len, def_header_len);
	strReply += context;
	if (bufferevent_write(_evbuffer, strReply.c_str(), strReply.length()) == -1) {
		LERROR << "Send client message failed." << _remoteIp;
		closeConnect();
	}
}

void CConnect::dispath(const string& context)
{
	_mapRecv.clear();
	stringToMap(context, _mapRecv, ";");
	string cmd = _mapRecv["cmd"];
	//登录
	if (cmd == "login")
		processLogin();
	//进入大厅
	else if (cmd == "hall")
		processHall();
	//进入桌子
	else if (cmd == "desk")
		processDesk();
	//未知命令
	else 
		processOther();
}

void CConnect::processLogin()
{
	string username = _mapRecv["user"];
	string password = _mapRecv["pass"];
	string type = _mapRecv["type"];
	if (username.length() < 4 || username.length() > 12
		|| password.length() < 6 || password.length() > 12) {
		replay("logntype=login;result=用户不存在或者密码错误");
		return;
	}
	if (type == "login") { //登录
		if (_player) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=login;result=重复登录");
			return;
		}
		playerInfoPtr ptr = dbmanager::Instance()->loadPlayer(username);
		if (!ptr || ptr->mPass != password){
			LERROR << "login faild, user not exist or pass error." << _remoteIp << "->" << username;
			replay("logntype=login;result=用户不存在或者密码错误");
			return;
		}
		_player = make_shared<CPlayer>();
		_player->setPlayerInfo(ptr);
		ostringstream os;
		os << "update dbt set logintime=now(), logincounts=" << ptr->mLoginCounts+1
			<< " where id=" << ptr->mId;
		dbmanager::Instance()->addSql(os.str());
		replay("logntype=login;result=ok");
	}
	else if (type == "regist"){ //注册
		if (_player) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=login;result=已经登录");
			return;
		}
		string  nickname = _mapRecv["nick"];
		
	}
}

void CConnect::processHall()
{

}

void CConnect::processDesk()
{

}

void CConnect::processOther()
{
	LERROR << "recv error commond" << _mapRecv["cmd"] << "->" << _remoteIp;
	closeConnect();
}
