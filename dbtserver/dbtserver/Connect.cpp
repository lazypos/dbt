#include "Connect.h"
#include "delegate.h"
#include "Global.h"
#include "Player.h"
#include "DBManager.h"
#include "Hall.h"

CConnect::CConnect()
{
}


CConnect::~CConnect()
{
}

bool CConnect::initConnect(struct event_base* ev, evutil_socket_t fd, const string& ip)
{
	_evbase = ev; _fd = fd; _remoteIp = ip;
	// �½����ݻ���
	_evbuffer = bufferevent_socket_new(_evbase, _fd, BEV_OPT_CLOSE_ON_FREE);
	if (_evbuffer == nullptr) {
		LERROR << "Connect init false. bufferevent_socket_new false." << ip;
		return false;
	}
	// ���ûص���ʹ�ܶ�д
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
	_bLogin = false;
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
	//��¼
	if (cmd == "login")
		processLogin();
	//�������
	else if (cmd == "hall")
		processHall();
	//��������
	else if (cmd == "desk")
		processDesk();
	//δ֪����
	else 
		processOther();
}

//��½����Ĵ���
void CConnect::processLogin()
{
	string username = _mapRecv["user"];
	string password = _mapRecv["pass"];
	string type = _mapRecv["type"];
	if (username.length() < 4 || username.length() > 12
		|| password.length() < 6 || password.length() > 12) {
		replay("logntype=login;result=�û������ڻ����������");
		return;
	}
	if (type == "login") { //��¼
		if (_bLogin) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=login;result=�ظ���¼");
			return;
		}
		_bLogin = true;
		playerInfoPtr ptr = dbmanager::Instance()->loadPlayer(username);
		if (!ptr || ptr->mPass != password){
			LERROR << "login faild, user not exist or pass error." << _remoteIp << "->" << username;
			replay("logntype=login;result=�û������ڻ����������");
			return;
		}
		setPlayerInfo(ptr);
		ostringstream os;
		os << "update dbt set logintime=now(), logincounts=" << ptr->mLoginCounts+1
			<< " where id=" << ptr->mId;
		dbmanager::Instance()->addSql(os.str());
		replay("logntype=login;result=ok");
	}
	else if (type == "regist"){ //ע��
		if (_bLogin) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=regist;result=�Ѿ���¼");
			return;
		}
		string  nickname = _mapRecv["nick"];
		if (nickname.length() < 2 || nickname.length() > 8){
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=regist;result=��Ϣ����");
			return;
		}
		if (dbmanager::Instance()->registPlayer(username, password, nickname)){
			LINFO << "ע��ɹ���" << _remoteIp << "->" << username;
			replay("logntype=regist;result=ok");
			return;
		}
		LERROR << "ע��ʧ�ܣ�" << _remoteIp << "->" << username;
		replay("logntype=regist;result=�˺��Ѵ���.");
		return;
	}
	LERROR << "�յ��������Ϣ." << _remoteIp;
}

//�����Ĵ���
void CConnect::processHall()
{
	ostringstream os;
	string type = _mapRecv["type"];
	if (type == "getmsg"){ //���������ȡ��Ҫ��Ϣ
		os << "halltype=getmsg;nick=" << getPlayerInfo()->mNick
			<< ";score=" << getPlayerInfo()->mScore
			<< ";total=" << getPlayerInfo()->mCount
			<< ";win=" << getPlayerInfo()->mWin * 100 / getPlayerInfo()->mCount << "%";
		replay(os.str());
	}else if (type == "add"){ //��������
		if (hallMgr::Instance()->addDesk(shared_from_this()) != -1) {
			replay("halltype=adddesk;result=ok");
			broadAddDesk(shared_from_this());
		}
		else 
			replay("halltype=adddesk;result=-1");
	}
	else if (type == "find") { //��������
		int id = atoi(_mapRecv["id"].c_str());
		if (hallMgr::Instance()->findDesk(shared_from_this(), id) != -1){
			replay("halltype=adddesk;result=ok"); 
			broadAddDesk(shared_from_this());
		}
		else
			replay("halltype=adddesk;result=-1");
	}
	else if (type == "create") {
		if (hallMgr::Instance()->createDesk(shared_from_this()) != -1) {
			replay("halltype=adddesk;result=ok");
			broadAddDesk(shared_from_this());
		}
		else
			replay("halltype=adddesk;result=-1");
	}
}

//���ӵĴ���
void CConnect::processDesk()
{

}

void CConnect::processOther()
{
	LERROR << "recv error commond" << _mapRecv["cmd"] << "->" << _remoteIp;
	closeConnect();
}

void CConnect::broadAddDesk(player_ptr ptr)
{
	int deskId = ptr->getDeskId();
	int seatId = ptr->getSeatId();

	ostringstream os;
	os << "desktype=play;state=add;player=" << seatId
		<< "<>" << ptr->getPlayerInfo()->mNick 
		<< "<>" << ptr->getPlayerInfo()->mScore
		<< "<>" << ptr->getPlayerInfo()->mCount 
		<< "<>" << ptr->getPlayerInfo()->mWin/ptr->getPlayerInfo()->mCount 
		<<"%<>" << ptr->getPlayerInfo()->mRun;
	//����Ҽ������Ϣ֪ͨ�������
	auto players = hallMgr::Instance()->getDeskInfo(deskId)->getPlayer();
	for (size_t i = 0; i < players.size(); ++i) {
		if (i != seatId && players[i] != nullptr){
			static_cast<CConnect*>(players[i].get())->replay(os.str());
		}
	}
}

void CConnect::broadLeaveDesk(player_ptr ptr)
{

}

void CConnect::broadReady(player_ptr ptr)
{

}
