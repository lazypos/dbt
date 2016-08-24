#include "Hall.h"



CHall::CHall()
{
}


CHall::~CHall()
{
}

int CHall::addDesk(player_ptr ptr)
{
	lock_guard<mutex>	ul(_muxHall);
	for (auto &it : _mapDesk) {
		int id = it.second->addPlayer(ptr);
		if (id != -1) {
			ptr->setDeskId(it.first);
			return it.first;
		}
	}
	return create_desk(ptr);
}

int CHall::findDesk(player_ptr ptr, int id)
{
	lock_guard<mutex>	ul(_muxHall);
	auto it = _mapDesk.find(id);
	if (it != _mapDesk.end()){
		if (it->second->addPlayer(ptr)) {
			ptr->setDeskId(it->first);
			return id;
		}
	}
	return -1;
}

int CHall::createDesk(player_ptr ptr)
{
	lock_guard<mutex>	ul(_muxHall);
	return create_desk(ptr);
}

desk_ptr CHall::getDeskInfo(int id)
{
	lock_guard<mutex>	ul(_muxHall);
	return _mapDesk[id];
}

int CHall::create_desk(player_ptr ptr)
{
	int id = 0;
	if (_mapDesk.empty())
		id = 1;
	else{
		id = _mapDesk.begin()->first;
		do {
			id++;
		} while (_mapDesk.find(id) != _mapDesk.end());
	}
	desk_ptr desk = make_shared<CDesk>(id);
	_mapDesk[id] = desk;
	LINFO << "create desk " << id;
	desk->addPlayer(ptr);
	ptr->setDeskId(id);
	return id;
}

void CHall::leave_desk(player_ptr ptr)
{
	lock_guard<mutex>	ul(_muxHall);
	desk_ptr pDesk = _mapDesk[ptr->getDeskId()];
	auto vecPlayers = pDesk->getPlayer();
	vecPlayers[ptr->getSeatId()] = nullptr;
	bool bdel = true;
	for (int i = 0; i < 4; i++) {
		if (vecPlayers[i] != nullptr) {
			bdel = false;
			break;
		}
	}
	if (bdel) 
		_mapDesk.erase(ptr->getDeskId());
}
