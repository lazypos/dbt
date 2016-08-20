#ifndef _h_CPlayer_h_
#define _h_CPlayer_h_
#include "header.h"
#include "define.h"

class CPlayer;
typedef shared_ptr<CPlayer> player_ptr;

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void	setPlayerInfo(playerInfoPtr ptr);

private:
	playerInfoPtr	_infoPtr;
};

#endif
