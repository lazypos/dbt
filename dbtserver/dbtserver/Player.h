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

	inline void		setPlayerInfo(playerInfoPtr ptr) {
		_infoPtr = ptr;
	}
	inline playerInfoPtr	getPlayerInfo() {
		return _infoPtr;
	}
	inline void		setDeskId(int id) {
		_deskId = id;
	}
	inline int		getDeskId() {
		return _deskId;
	}
	inline void		setSeatId(int id) {
		_seatId = id;
	}
	inline int		getSeatId() {
		return _seatId;
	}
protected:
	playerInfoPtr	_infoPtr;
	int				_deskId = -1;
	int				_seatId = -1;
};

#endif
