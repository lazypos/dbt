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

	inline void		setScore(int n) {
		_nowScore = n;
	}
	inline	int		getScore() {
		return _nowScore;
	}
	inline void		lastPut(int n) {
		_lastPutPlayers = n;
	}
	inline	int		getLastPut() {
		return _lastPutPlayers;
	}
	inline	void	setGo(int n) {
		_goSeq = n;
	}
	inline	int		getGo() {
		return _goSeq;
	}

	void	reStart();
	void	leave(player_ptr ptr);

	vector<int>				_lastPutCards;
private:
	int						_deskId = 0;
	mutex					_muxDesk;
	vector<player_ptr>		_vecPlayers;
	int						_nowScore = 0;
	int						_lastPutPlayers = 0;
	int						_goSeq = 0;
};

#endif
