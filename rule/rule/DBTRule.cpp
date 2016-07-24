#include "stdafx.h"
#include "DBTRule.h"


CDBTRule::CDBTRule()
{
}


CDBTRule::~CDBTRule()
{
}

void CDBTRule::shuffleCards(std::array<int, 216>& arrCards, int times)
{
	for (int i=0; i<216; i++)
		arrCards[i] = i/4;
	
	int temp = 0;
	std::random_device rd;
	for (int i=0; i<times; i++){
		for (size_t j=0; j<arrCards.size(); j++){
			int s = rd() % 216;
			temp = arrCards[j];
			arrCards[j] = arrCards[s];
			arrCards[s] = temp;
		}
	}
}
