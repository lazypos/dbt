#pragma once
#include <array>
#include <random>
#include <vector>

class CDBTRule
{
public:
	CDBTRule();
	~CDBTRule();

	static void shuffleCards(std::array<int,216>& arrCards, int times);


	static	bool	checkCards(std::vector<int>& cards);

	static	int		getValue(int card) { return card / 4; };
	static	int		getColor(int card) { return card % 4; }
	static  bool	isJoker(int card) { return getValue(card) == 13; };
	static	bool	isRedFive(int card) { return (getValue(card) == 4 && getColor(card) == 3); };
	static  int		getWeight(int card);


	static	bool	isSingle(const std::vector<int>& cards);
	static  bool	isPair(const std::vector<int>& cards);
	static	bool	isthreed(const std::vector<int>& cards);
	static	bool	isAtom(const std::vector<int>& cards);
	static	bool	isBoom(const std::vector<int>& cards);
	static	bool	isSister(const std::vector<int>& cards);
	static	bool	isPlane(const std::vector<int>& cards);
};

