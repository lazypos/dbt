#include "Desk.h"

CDesk::CDesk(int id)
	:	_deskId(id)
{
	_vecPlayers.resize(4);
}


CDesk::~CDesk()
{
}

int CDesk::addPlayer(player_ptr ptr)
{
	lock_guard<mutex> ul(_muxDesk);
	for (size_t i = 0; i < _vecPlayers.size(); ++i) {
		if (_vecPlayers[i] == nullptr){
			_vecPlayers[i] == ptr;
			return i;
		}
	}
	return -1;
}

std::vector<player_ptr> CDesk::getPlayer()
{
	lock_guard<mutex> ul(_muxDesk);
	return _vecPlayers;
}

void CDesk::reStart()
{
	_nowScore = 0;
	_goSeq = 0;
	for (int i = 0; i < 4; i++) {
		_vecPlayers[i]->reStart();
	}
}

