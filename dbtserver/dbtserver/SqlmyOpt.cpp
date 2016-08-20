#include "SqlmyOpt.h"


CSqlmyOpt::CSqlmyOpt()
{
}


CSqlmyOpt::~CSqlmyOpt()
{
}

bool CSqlmyOpt::open()
{
	close();
	_connPtr = mysql_init(nullptr);
	if (_connPtr == nullptr) {
		LERROR << "init mysql faild.";
		return false;
	}

	if (!mysql_real_connect(_connPtr, _host.c_str(), _user.c_str(),
		_pass.c_str(), _name.c_str(), atoi(_port.c_str()),
		nullptr, CLIENT_MULTI_STATEMENTS)) {
		LERROR << "connect mysql faild." << _host;
		return false;
	}
	
	mysql_set_character_set(_connPtr, "utf8");
	setConnect(true);
	return true;
}

void CSqlmyOpt::close()
{
	setConnect(false);
	if (_connPtr){
		mysql_close(_connPtr);
		_connPtr = nullptr;
	}
}

bool CSqlmyOpt::query(const std::string& sql, DBResultPtr& ptr)
{
	std::lock_guard<std::mutex> lg(_mutex);
	bool success = true;
	while (!isConnected()) {
		if (open()) break;
		LERROR << "reconnect db faild.";
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	if (mysql_real_query(_connPtr, sql.c_str(), sql.length())){
		success = false;
		LERROR << "query sql error:" << sql;
		long errcode = 0;
		getLastError(errcode);
		if (errcode == 2006){
			LERROR << "db breaked.";
			close();
		}
	}
	MYSQL_RES* res = mysql_store_result(_connPtr);
	if (success && res)
		ptr = std::make_shared<CSqlmyResult>(res);
	
	return success;
}

bool CSqlmyOpt::execute(const std::string& sql)
{
	std::lock_guard<std::mutex> lg(_mutex);
	bool success = true;
	while (!isConnected()) {
		if (open()) break;
		LERROR << "reconnect db faild.";
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	if (mysql_real_query(_connPtr, sql.c_str(), sql.length())) {
		success = false;
		LERROR << "execute sql faild:" << sql;
		long errcode = 0;
		getLastError(errcode);
		if (errcode == 2006) {
			LERROR << "db breaked.";
			close();
		}
	}
	clean();
	return success;
}

const std::string CSqlmyOpt::getLastError(long& errCode)
{
	const char* err = mysql_error(_connPtr);
	errCode = mysql_errno(_connPtr);
	if (err)
		return err;
	return "";
}

void CSqlmyOpt::clean()
{
	MYSQL_RES* res = mysql_store_result(_connPtr);
	if (res)
		mysql_free_result(res);
	while (mysql_next_result(_connPtr) == 0)
	{
		res = mysql_store_result(_connPtr);
		if (res)
			mysql_free_result(res);
	}
}
