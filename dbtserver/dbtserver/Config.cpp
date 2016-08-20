#include "Config.h"
#include "Global.h"

CConfig::CConfig()
{
}


CConfig::~CConfig()
{
}

bool CConfig::start()
{
	_exit = false;
	_threadChk = make_shared<thread>(&CConfig::work, this);
	_threadChk->detach();
	return true;
}

void CConfig::work()
{
	while (!_exit) {
		this_thread::sleep_for(chrono::seconds(3));
		if (atoi(readFile("exit.flag").c_str()))
			_exit = true;
	}
}
