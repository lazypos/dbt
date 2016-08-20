#ifndef _h_CDBManager_h_
#define _h_CDBManager_h_
#include "header.h"
#include "SqlmyOpt.h"
#include "common.h"
#include "define.h"

class CDBManager
{
public:
	CDBManager();
	~CDBManager();


	bool	start();
	playerInfoPtr	loadPlayer(const string& user);
	bool	registPlayer(const string& user, const string& pass, const string nick);
	void	addSql(const string& sql);

protected:
	void	work();

private:
	CSqlmyOpt		_dbopt;
	thread_ptr		_threadInsert;
	list<string>	_lstSql;
	mutex			_mux;
};

typedef CMySingleton<CDBManager> dbmanager;

#endif
