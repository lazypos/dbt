#ifndef _h_CHall_h_
#define _h_CHall_h_
#include "Desk.h"
#include "common.h"

class CHall
{
public:
	CHall();
	~CHall();

	int		addDesk(player_ptr ptr);
	int		findDesk(player_ptr ptr, int id);
	int		createDesk(player_ptr ptr);

	desk_ptr	getDeskInfo(int id);

protected:
	int		create_desk(player_ptr ptr);
private:
	map<int, desk_ptr>	_mapDesk;
	mutex				_muxDesk;
};

typedef CMySingleton<CHall> hallMgr;

#endif
