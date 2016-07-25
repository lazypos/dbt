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
	//与序号相关，A/2/Jocket/5特殊处理
	int nWeight = card - 8;
	if (getValue(card) == 0 || getValue(card) == 1)
		nWeight += 48;
	if (isJoker(card))
		nWeight += 8;
	if (isRedFive(card))
		nWeight = 54;
	return nWeight;
}

int CDBTRule::getWeightNoRedFive(int card)
{
	//与序号相关，A/2/Jocket特殊处理
	int nWeight = card - 8;
	if (getValue(card) == 0 || getValue(card) == 1)
		nWeight += 48;
	if (isJoker(card))
		nWeight += 8;
	return nWeight;
}

bool CDBTRule::isNormal(const cards_type ty)
{
	return (ty != type_boom && ty != type_atom);
}

bool CDBTRule::isSingle(const std::vector<int>& cards)
{
	return cards.size() == 1;
}

bool CDBTRule::isPairs(const std::vector<int>& cards)
{
	if (cards.size() == 2 && getValue(cards[0]) == getValue(cards[1])){
		//jocker颜色一样
		if ((cards[0] == 53 && cards[1] == 54) || (cards[0] == 54 && cards[1] == 53))
			return false;
	}
	return false;
}

bool CDBTRule::isthree(const std::vector<int>& cards)
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
	if (num < 8 || num > 24 || num % 2 != 0 || isJoker(cards[num - 1]))
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
		for (size_t i = 0; i < cards.size()-2; i += 2) {
			if (getValue(cards[i]) + 1 != getValue(cards[i + 2]))
				return false;
		}
	}
	return true;
}

bool CDBTRule::isPlane(const std::vector<int>& cards)
{
	size_t num = cards.size();
	if (num < 9 || num > 36 || num % 3 != 0 || isJoker(cards[num - 1]))
		return false;
	for (size_t i = 0; i < cards.size(); i += 3)
		if ((getValue(cards[i]) != getValue(cards[i + 1])) 
			|| (getValue(cards[i]) != getValue(cards[i + 2])))
			return false;

	//带A递增只允许345678910JQKA
	if (getValue(cards[0]) == 0) {
		if (getValue(cards[num - 1] != 12))
			return false;
		for (size_t i = 3; i < cards.size() - 3; i += 3) {
			if (getValue(cards[i]) + 1 != getValue(cards[i + 3]))
				return false;
		}
	}
	//不带A
	else {
		for (size_t i = 0; i < cards.size() - 3; i += 3) {
			if (getValue(cards[i]) + 1 != getValue(cards[i + 3]))
				return false;
		}
	}
	return true;
}

bool CDBTRule::isThreetwo(const std::vector<int>& cards)
{
	if (cards.size() != 5 || isBoom(cards))
		return false;
	//AAABB
	if (getValue(cards[0]) == getValue(cards[1]) == getValue(cards[2])){
		if (isJoker(cards[3]) && cards[3] != cards[4])
			return false;
		if (isJoker(cards[0]) && (cards[0] != cards[1] || cards[0] != cards[2]))
			return false;
		if (getValue(cards[3]) != getValue(cards[4]))
			return false;
		return true;
	}
	//BBAAA
	if (getValue(cards[2]) == getValue(cards[3]) == getValue(cards[4])){
		if (isJoker(cards[0]) && cards[0] != cards[1])
			return false;
		if (isJoker(cards[2]) && (cards[2] != cards[3] || cards[2] != cards[4]))
			return false;
		if (getValue(cards[0]) != getValue(cards[1]))
			return false;
		return true;
	}
	return false;
}

std::pair<CDBTRule::cards_type, int> CDBTRule::getType(const std::vector<int>& cards)
{
	if (isSingle(cards))
		return std::make_pair(type_singal, getWeight(cards[0]));
	else if (isPairs(cards))
		return std::make_pair(type_pairs, getWeightNoRedFive(cards[1]));
	else if (isthree(cards))
		return std::make_pair(type_three, getWeightNoRedFive(cards[2]));
	else if (isBoom(cards))
		return std::make_pair(type_boom, getWeightNoRedFive(cards[cards.size() - 1]));
	else if (isAtom(cards))
		return std::make_pair(type_atom, getWeight(cards[cards.size() - 1]));
	else if (isSister(cards)) {
		//带A
		if (getValue(cards[0]) == 0)
			return std::make_pair(type_sister, getWeightNoRedFive(cards[1]));
		return std::make_pair(type_sister, getWeightNoRedFive(cards[cards.size() - 1]));
	}
	else if (isPlane(cards)) {
		//带A
		if (getValue(cards[0]) == 0)
			return std::make_pair(type_plane, getWeightNoRedFive(cards[2]));
		return std::make_pair(type_plane, getWeightNoRedFive(cards[cards.size() - 1]));
	}
	else if (isThreetwo(cards)){
		//AAABB
		if (getValue(cards[1]) == getValue(cards[2])){
			return std::make_pair(type_three, getWeightNoRedFive(cards[2]));
		}
		//AABBB
		return std::make_pair(type_three, getWeightNoRedFive(cards[4]));
	}
	return std::make_pair(type_unknow, 0);
}

bool CDBTRule::isBigger(const std::vector<int>& cards_per, const std::vector<int>& cards_now)
{
	auto per = getType(cards_per);
	auto now = getType(cards_now);
	//前一次最大或本次类型不对
	if (now.first == type_unknow || per.second == 54)
		return false;
	if (isNormal(per.first) && isNormal(now.first)){
		//必须类型数量一样
		if (per.first == now.first && cards_per.size() == cards_now.size())
			return now.second > per.second;
		return false;
	}
	if (!isNormal(per.first) && !isNormal(now.first)) {
		if ((per.first == type_boom && now.first == type_boom)
			|| (per.first == type_atom && now.first == type_atom)){
			//数量多的大
			if (cards_per.size() == cards_now.size())
				return now.second > per.second;
			return cards_now.size() > cards_per.size();
		}
		if (per.first == type_atom && now.first == type_boom)
			return false;
		return true;
	}
	if (!isNormal(per.first) && isNormal(now.first))
		return false;
	return true;
}

int CDBTRule::getScore(const std::vector<int>& cards)
{
	int score = 0;
	for_each(cards.begin(), cards.end(), [&score](int i) {
		int val = getValue(i);
		if (val == 4)
			score += 5;
		else if (val == 9 || val == 12)
			score += 10;
	});
	return score;
}

CDBTRule::over_blance CDBTRule::isOver(int seatId, 
	const std::vector< std::pair<int, int> >& vecInfo)
{
	return over_not;
}
