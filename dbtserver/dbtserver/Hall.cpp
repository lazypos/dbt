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
			ptr->setSeatId(id);
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
		if (it->second->addPlayer(ptr))
			return id;
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
	else
		id = _mapDesk.rbegin()->first;
	do {
		id++;
	} while (_mapDesk.find(id) != _mapDesk.end());
	desk_ptr desk = make_shared<CDesk>(id);
	_mapDesk[id] = desk;
	LINFO << "create desk " << id;
	ptr->setDeskId(id);
	return id;
}
