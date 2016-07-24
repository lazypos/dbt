#pragma once
#include <array>
#include <random>

class CDBTRule
{
public:
	CDBTRule();
	~CDBTRule();

	static void shuffleCards(std::array<int,216>& arrCards, int times);
};

