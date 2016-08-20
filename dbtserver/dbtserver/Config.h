#ifndef _h_CConfig_h_
#define _h_CConfig_h_
#include "header.h"
#include "common.h"
#include "define.h"

class CConfig
{
public:
	CConfig();
	~CConfig();

	bool	start();
	bool	isExit() { return _exit; }

protected:
	void	work();

private:
	bool		_exit = false;
	thread_ptr	_threadChk;
};
typedef CMySingleton<CConfig> configMgr;

#endif

