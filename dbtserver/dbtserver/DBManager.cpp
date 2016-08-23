#include "DBManager.h"
#include "define.h"
#include "Config.h"
#include "LoginSvr.h"

CDBManager::CDBManager()
{
}


CDBManager::~CDBManager()
{
}

bool CDBManager::start()
{
	_dbopt.setConnectParameter("42.96.205.100", "3306", "", "root", "Adabaoge,.");
	if (!_dbopt.execute("use zcw")) {
		LERROR << "can't use zcw db.";
		return false;
	}
	_threadInsert = make_shared<thread>(&CDBManager::work, this);
	_threadInsert->detach();
	return true;
}

playerInfoPtr CDBManager::loadPlayer(const string& user)
{
	if (user.empty())
		return nullptr;

	ostringstream os;
	os << "select * from dbt where username='" << user << "' limit 1;";
	DBResultPtr ptr;
	if (_dbopt.query(os.str(), ptr)){
		if (!ptr->IsEof()){
			playerInfoPtr pInfo = make_shared<stPlayerInfo>();
			pInfo->mId = ptr->GetValueAsInt(0);
			pInfo->mUser = ptr->GetValue(1);
			pInfo->mPass = ptr->GetValue(2);
			pInfo->mNick = ptr->GetValue(3);
			pInfo->mCount = ptr->GetValueAsInt(4);
			pInfo->mWin = ptr->GetValueAsInt(5);
			pInfo->mRun = ptr->GetValueAsInt(6);
			pInfo->mLoginCounts = ptr->GetValueAsInt(7);
			pInfo->mScore = ptr->GetValueAsInt(8);
			return pInfo;
		}
	}
	return nullptr;
}

bool CDBManager::registPlayer(const string& user, const string& pass, const string nick)
{
	string sql = "select * from dbt where user='" + user + "'";
	DBResultPtr ptr;
	if (_dbopt.query(sql, ptr) && ptr->IsEof()){
		sql = "insert into dbt (username,password,nickname) values('"
			+ user + "','" + pass + "','" + nick + "')";
		return _dbopt.execute(sql);
	}
	return false;
}

void CDBManager::addSql(const string& sql)
{
	unique_lock<mutex> lk(_mux);
	_lstSql.push_back(sql);
}

void CDBManager::work()
{
	list<string> lstTmp;
	while (!configMgr::Instance()->isExit()){
		_mux.lock();
		lstTmp.swap(_lstSql);
		_mux.unlock();

		for (const auto &it : lstTmp){
			if (!_dbopt.execute(it))
				LERROR << "insert db faild:" << it;
		}
		lstTmp.clear();
		this_thread::yield();
	}
	//ÍË³öÇ°
	for (const auto &it : _lstSql) {
		if (!_dbopt.execute(it))
			LERROR << "insert db faild:" << it;
	}
	loginSvr::Instance()->stop();
}
