#ifndef _h_CDesk_h_
#define _h_CDesk_h_
#include "header.h"
#include "Player.h"

class CDesk;
typedef shared_ptr<CDesk> desk_ptr;

class CDesk
{
public:
	explicit CDesk(int id);
	~CDesk();

	int		addPlayer(player_ptr ptr);
	vector<player_ptr> getPlayer();

private:
	int					_deskId = 0;
	mutex				_muxDesk;
	vector<player_ptr>	_vecPlayers;
};

#endif
