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

bool CDBTRule::checkCards(std::vector<int>& cards)
{
	for (size_t i = 0; i < cards.size(); ++i) {
		if (cards[i] < 0 || cards[i] > 53)
			return false;
	}
	sort(cards.begin(), cards.end());
	return true;
}

int CDBTRule::getWeight(int card)
{
	//与序号相关，A/2/5特殊处理
	int nWeight = card - 8;
	if (getValue(card) == 0 || getValue(card) == 1)
		nWeight += 48;
	if (isJoker(card))
		nWeight += 8;
	if (isRedFive(card))
		nWeight = 54;
	return nWeight;
}

bool CDBTRule::isSingle(const std::vector<int>& cards)
{
	return cards.size() == 1;
}

bool CDBTRule::isPair(const std::vector<int>& cards)
{
	if (cards.size() == 2 && getValue(cards[0]) == getValue(cards[1])){
		//jocker颜色一样
		if ((cards[0] == 53 && cards[1] == 54) || (cards[0] == 54 && cards[1] == 53))
			return false;
	}
	return false;
}

bool CDBTRule::isthreed(const std::vector<int>& cards)
{
	if (cards.size() != 3 || isAtom(cards) || isJoker(cards[0]))
		return false;

	if (cards[0] == cards[1] == cards[2])
		return true;
	return false;
}

bool CDBTRule::isAtom(const std::vector<int>& cards)
{
	if (cards.size() == 3 && cards[0] == cards[1] == cards[2])
		return true;
	if (cards.size() == 4 && cards[0] == cards[1] == cards[2] == cards[3])
		return true;
	return false;
}

bool CDBTRule::isBoom(const std::vector<int>& cards)
{
	if (cards.size() < 4 || cards.size() > 16 || isAtom(cards) || isJoker(cards[0]))
		return false;

	int val = getValue(cards[0]);
	for (size_t i = 1; i < cards.size(); i++) {
		if (getValue(cards[i]) != val)
			return false;
	}
	return true;
}

bool CDBTRule::isSister(const std::vector<int>& cards)
{
	size_t num = cards.size();
	if (num < 6 || num > 24 || num % 2 != 0 || isJoker(cards[num - 1]))
		return false;

	for (size_t i = 0; i < cards.size(); i += 2)
		if (getValue(cards[i]) != getValue(cards[i + 1]))
			return false;
	//带A递增只允许345678910JQKA
	if (getValue(cards[0]) == 0){
		if (getValue(cards[num - 1] != 12))
			return false;
		for (size_t i = 2; i < cards.size()-2; i += 2) {
			if (getValue(cards[i]) + 1 != getValue(cards[i + 2]))
				return false;
		}
	}
	//不带A
	else {
		for (size_t i = 0; i < cards.size() - 2; i += 2) {
			if (getValue(cards[i]) + 1 != getValue(cards[i + 2]))
				return false;
		}
	}
	return true;
}
