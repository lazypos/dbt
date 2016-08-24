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
	inline int		isReady() {
		return _ready;
	}
	inline void		onReady() {
		_ready = 1;
	}
	inline void		Score(int s) {
		_getScore += s;
	}
	inline int		getScore() {
		return _getScore;
	}
	inline bool		isOver() {
		return _isOver;
	}
	inline void		isOver(bool b) {
		_isOver = b;
	}
	inline int		getGoneNum() {
		return _goneNum;
	}
	inline void		setGoneNum(int n) {
		_goneNum = n;
	}
	void	reStart();

protected:
	playerInfoPtr	_infoPtr;
	int				_deskId = -1;
	int				_seatId = -1;
	int				_ready = 0;
	int				_getScore = 0;
	vector<int>		_vecCards;
	bool			_isOver = false;
	int				_goneNum = 0;
};

#endif
