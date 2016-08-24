#include "Connect.h"
#include "delegate.h"
#include "Global.h"
#include "Player.h"
#include "DBManager.h"
#include "Hall.h"
#include "DBTRule.h"

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

//登陆界面的处理
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
		if (_bLogin) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=login;result=重复登录");
			return;
		}
		_bLogin = true;
		playerInfoPtr ptr = dbmanager::Instance()->loadPlayer(username);
		if (!ptr || ptr->mPass != password){
			LERROR << "login faild, user not exist or pass error." << _remoteIp << "->" << username;
			replay("logntype=login;result=用户不存在或者密码错误");
			return;
		}
		setPlayerInfo(ptr);
		ostringstream os;
		os << "update dbt set logintime=now(), logincounts=" << ptr->mLoginCounts+1
			<< " where id=" << ptr->mId;
		dbmanager::Instance()->addSql(os.str());
		replay("logntype=login;result=ok");
	}
	else if (type == "regist"){ //注册
		if (_bLogin) {
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=regist;result=已经登录");
			return;
		}
		string  nickname = _mapRecv["nick"];
		if (nickname.length() < 2 || nickname.length() > 8){
			LERROR << "." << _remoteIp << "->" << username;
			replay("logntype=regist;result=信息有误");
			return;
		}
		if (dbmanager::Instance()->registPlayer(username, password, nickname)){
			LINFO << "注册成功！" << _remoteIp << "->" << username;
			replay("logntype=regist;result=ok");
			return;
		}
		LERROR << "注册失败！" << _remoteIp << "->" << username;
		replay("logntype=regist;result=账号已存在.");
		return;
	}
	LERROR << "收到错误的消息." << _remoteIp;
}

//大厅的处理
void CConnect::processHall()
{
	string type = _mapRecv["type"];
	if (type == "getmsg"){ //进入大厅获取必要信息
		ostringstream os;
		os << "halltype=getmsg;nick=" << getPlayerInfo()->mNick
			<< ";score=" << getPlayerInfo()->mScore
			<< ";total=" << getPlayerInfo()->mCount
			<< ";win=" << getPlayerInfo()->mWin * 100 / getPlayerInfo()->mCount << "%";
		replay(os.str());
	}else if (type == "add"){ //加入桌子
		if (hallMgr::Instance()->addDesk(shared_from_this()) != -1) {
			replay("halltype=adddesk;result=ok");
			broadAddDesk();
		}
		else 
			replay("halltype=adddesk;result=-1");
	}
	else if (type == "find") { //查找桌子
		int id = atoi(_mapRecv["id"].c_str());
		if (hallMgr::Instance()->findDesk(shared_from_this(), id) != -1){
			replay("halltype=adddesk;result=ok"); 
			broadAddDesk();
		}
		else
			replay("halltype=adddesk;result=-1");
	}
	else if (type == "create") {
		if (hallMgr::Instance()->createDesk(shared_from_this()) != -1) {
			replay("halltype=adddesk;result=ok");
			broadAddDesk();
		}
		else
			replay("halltype=adddesk;result=-1");
	}
}

//桌子的处理
void CConnect::processDesk()
{
	string type = _mapRecv["type"];
	if (type == "getmsg") { //获取当前座位上的其他玩家信息
		processGetmsg();
	} else if (type == "ready"){ //准备
		broadReady();
	}else if (type == "quit") { //离开
		broadLeaveDesk();
	}else if (type == "put") { //出牌
		processPutCards();
	}else if (type == "noput") { //不出牌
		processPutCards();
	}
}

void CConnect::processOther()
{
	LERROR << "recv error commond" << _mapRecv["cmd"] << "->" << _remoteIp;
	closeConnect();
}

void CConnect::broadAddDesk()
{
	ostringstream os;
	os << "desktype=play;state=add;player=" << _seatId
		<< "<>" << getPlayerInfo()->mNick 
		<< "<>" << getPlayerInfo()->mScore
		<< "<>" << getPlayerInfo()->mCount 
		<< "<>" << getPlayerInfo()->mWin/getPlayerInfo()->mCount 
		<<"%<>0";
	//通知其他玩家
	auto players = hallMgr::Instance()->getDeskInfo(_deskId)->getPlayer();
	for (size_t i = 0; i < players.size(); ++i) {
		if (i != _seatId && players[i] != nullptr)
			static_cast<CConnect*>(players[i].get())->replay(os.str());
	}
}

void CConnect::broadLeaveDesk()
{
	ostringstream os;
	os << "desktype=play;state=leave;id=" << _seatId;
	//将玩家加入的信息通知其他玩家
	auto players = hallMgr::Instance()->getDeskInfo(_deskId)->getPlayer();
	for (size_t i = 0; i < players.size(); ++i) {
		if (i != _seatId && players[i] != nullptr)
			static_cast<CConnect*>(players[i].get())->replay(os.str());
	}
}

void CConnect::broadReady()
{
	onReady();
	ostringstream os;
	os << "desktype=play;state=ready;id=" << _seatId;
	//讲玩家加入的信息通知其他玩家
	auto players = hallMgr::Instance()->getDeskInfo(_deskId)->getPlayer();
	size_t readyCounts = 0;
	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i] != nullptr) {
			if (players[i]->isReady())
				readyCounts++;
			if (i != _seatId)
				static_cast<CConnect*>(players[i].get())->replay(os.str());
		}
	}
	//如果所有人都已准备,游戏开始
	desk_ptr pDesk = hallMgr::Instance()->getDeskInfo(_deskId);
	if (readyCounts == players.size()){
		//洗牌
		std::array<int, 216> cards;
		CDBTRule::shuffleCards(cards);
		std::random_device rd;
		int startPlayId = rd() % 4;
		pDesk->reStart();
		pDesk->lastPut(startPlayId);
		//发牌
		for (int i=0; i<4; i++){
			os.str("");
			//desktype=play;state=start;now=1;cards=1,1,3,4,5,6,12,12,34,34,4,42,42,32,12,23,4,6,7,32,25,23,23,21,23,53,45,45,45,6,32,53,15,32,38,40,29,29,28,39,38
			os << "desktype=play;state=start;now=" << startPlayId << ";cards=";
			for (int j = 0; j < 54; j++) {
			
				os << cards[i + 4 * j] << ",";
			}
			static_cast<CConnect*>(players[i].get())->replay(os.str());
		}
	}
}

void CConnect::processGetmsg()
{
	//desktype=getmsg;desknum=78;id=1;player=0<>cbs<>2300<>12<>80%<>1|1<>1dsa<>111<>123<>60%<>0|3<>cjl<>1200<>324<>30%<>0
	ostringstream os;
	os << "desktype=getmsg;desknum=" << _deskId << ";id=" << _seatId;
	auto players = hallMgr::Instance()->getDeskInfo(_deskId)->getPlayer();
	ostringstream osplayers;
	for (size_t i = 0; i < players.size(); ++i) {
		if(players[i] != nullptr) {
			osplayers << i
				<< "<>" << players[i]->getPlayerInfo()->mNick
				<< "<>" << players[i]->getPlayerInfo()->mScore
				<< "<>" << players[i]->getPlayerInfo()->mCount
				<< "<>" << players[i]->getPlayerInfo()->mWin / players[i]->getPlayerInfo()->mCount
				<< "%<>" << players[i]->isReady()
				<< "|";
		}
	}
	if (osplayers.str().length()){
		os << ";player=" << osplayers.str();
	}
	replay(os.str());
}

void CConnect::processPutCards()
{
	//desktype=play;state=over;n0=dsad;n1=dsad;n2=player3;n3=dsads;s0=20;s1=-20;s2=20;s3=-20
// 	auto players = hallMgr::Instance()->getDeskInfo(_deskId)->getPlayer();
// 	ostringstream os;
// 	os << "desktype=play;state=over;"
// 		<< "n0=" << 
}

void CConnect::processNoPutCards()
{
	//=> desktype=play;state=put;per=3;now=0;cards=;surplus=30;clear=1;0=120;1=230;n=15
	desk_ptr pDesk = hallMgr::Instance()->getDeskInfo(_deskId);
	if (pDesk->getLastPut() == _seatId){ //不允许不出牌
		//int putCard = _vecCards[0];
		return;
	}
	//不出牌
	auto players = pDesk->getPlayer();
	int score0 = players[0]->getScore() + players[2]->getScore();
	int score1 = players[1]->getScore() + players[3]->getScore();
	
	//计算下一个出牌的
	int nextPut = 0;
	for (size_t i = 0; i < 4; i++) {
		if (!players[(_seatId + 1) % 4]->isOver())
			nextPut = (_seatId + 1) % 4;
	}
	//大了一轮，算分
	if (pDesk->getLastPut() == nextPut) {
		if (pDesk->getLastPut() % 2 == 0)
			score0 += pDesk->getScore();
		else
			score1 += pDesk->getScore();
		pDesk->setScore(0);
		//是否结束
		if (isGameOver())
			return;
	}

	ostringstream os;
	os << "desktype=play;state=put;per=" << _seatId
		<< ";now=" << (_seatId + 1) % 4
		<< ";cards=;surplus=" << _vecCards.size()
		<< ";clear=1;0=" << score0
		<< ";1=" << score1
		<< ";n=" << pDesk->getScore();
	replay(os.str());
}

bool CConnect::isGameOver()
{
	//desktype=play;state=over;n0=dsad;n1=dsad;n2=player3;n3=dsads;s0=20;s1=-20;s2=20;s3=-20
	desk_ptr pDesk = hallMgr::Instance()->getDeskInfo(_deskId);
	auto players = pDesk->getPlayer();
	//是否结束
	std::vector< std::pair<int, int> > tmp;
	for (int i = 0; i < 4; i++)
		tmp.emplace_back(make_pair(players[i]->getGoneNum(), players[i]->getScore()));
	auto rst = CDBTRule::isOver(_seatId, tmp);
	if (rst != CDBTRule::over_not) { //游戏结束
		ostringstream os;
		os << "desktype=play;state=over;n0=" << players[0]->getPlayerInfo()->mNick
			<< ";n1=" << players[1]->getPlayerInfo()->mNick
			<< ";n2=" << players[2]->getPlayerInfo()->mNick
			<< ";n3=" << players[3]->getPlayerInfo()->mNick;
		int n = 0;
		if (rst == CDBTRule::over_draw) { //平局
			os << ";s0=0;s1=0;s2=0;s3=0";
		} else {
			if (rst == CDBTRule::over_lose) { //输
				os << ";s" << n << "=" << "-10"
					<< ";s" << (n + 1) % 4 << "=" << "10"
					<< ";s" << (n + 2) % 4 << "=" << "-10"
					<< ";s" << (n + 3) % 4 << "=" << "10";
			}else if (rst == CDBTRule::over_lose_dual){
				os << ";s" << n << "=" << "-20"
					<< ";s" << (n + 1) % 4 << "=" << "20"
					<< ";s" << (n + 2) % 4 << "=" << "-20"
					<< ";s" << (n + 3) % 4 << "=" << "20";
			}else if (rst == CDBTRule::over_lose_quad) {
				os << ";s" << n << "=" << "-40"
					<< ";s" << (n + 1) % 4 << "=" << "40"
					<< ";s" << (n + 2) % 4 << "=" << "-40"
					<< ";s" << (n + 3) % 4 << "=" << "40";
			}else if (rst == CDBTRule::over_win) { //赢
				os << ";s" << n << "=" << "10"
					<< ";s" << (n + 1) % 4 << "=" << "-10"
					<< ";s" << (n + 2) % 4 << "=" << "10"
					<< ";s" << (n + 3) % 4 << "=" << "-10";
			}else if (rst == CDBTRule::over_win_dual) {
				os << ";s" << n << "=" << "20"
					<< ";s" << (n + 1) % 4 << "=" << "-20"
					<< ";s" << (n + 2) % 4 << "=" << "20"
					<< ";s" << (n + 3) % 4 << "=" << "-20";
			}else if (rst == CDBTRule::over_win_quad) {
				os << ";s" << n << "=" << "40"
					<< ";s" << (n + 1) % 4 << "=" << "-40"
					<< ";s" << (n + 2) % 4 << "=" << "40"
					<< ";s" << (n + 3) % 4 << "=" << "-40";
			}
		}
		replay(os.str());
		pDesk->reStart();
		return true;
	}
	return false;
}

