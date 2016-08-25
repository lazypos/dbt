#include "Hall.h"



CHall::CHall()
{
}


CHall::~CHall()
{
}

int CHall::addDesk(player_ptr ptr)
{
	if (ptr->getDeskId() != -1) {
		return -1;
	}
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
	if (ptr->getDeskId() != -1) {
		return -1;
	}
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
	if (ptr->getDeskId() != -1) {
		return -1;
	}
	lock_guard<mutex>	ul(_muxHall);
	return create_desk(ptr);
}

desk_ptr CHall::getDeskInfo(int id)
{
	lock_guard<mutex>	ul(_muxHall);
	return _mapDesk[id];
}

void CHall::leave_desk(player_ptr ptr)
{
	lock_guard<mutex>	ul(_muxHall);
	auto pDesk = _mapDesk[ptr->getDeskId()];
	pDesk->leave(ptr);
	auto players = pDesk->getPlayer();
	bool bdel = true;
	for (int i=0; i<4; i++){
		if (players[i] != nullptr){
			bdel = false;
			break;
		}
	}
	if (bdel)
		_mapDesk.erase(ptr->getDeskId());
}

int CHall::create_desk(player_ptr ptr)
{
	int id = 0;
	if (_mapDesk.empty())
		id = 1;
	else {
		do {
			id = _mapDesk.begin()->first;
			id++;
		} while (_mapDesk.find(id) != _mapDesk.end());
	}
	desk_ptr pDesk = make_shared<CDesk>(id);
	_mapDesk[id] = pDesk;
	LINFO << "create desk " << id;
	pDesk->addPlayer(ptr);
	ptr->setDeskId(id);
	return id;
}
