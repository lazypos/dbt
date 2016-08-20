#ifndef _h_CHall_h_
#define _h_CHall_h_
#include "Desk.h"

class CHall
{
public:
	CHall();
	~CHall();

private:
	map<int, desk_ptr>	_mapDesk;
};

#endif
