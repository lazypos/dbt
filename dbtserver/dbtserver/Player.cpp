#include "Player.h"



CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::reStart()
{
	_getScore = 0;
	_vecCards.clear();
	_isOver = false;
	_ready = false;
	_goneNum = 0;
}
