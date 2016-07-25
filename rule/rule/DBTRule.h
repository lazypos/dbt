#pragma once
#include <array>
#include <random>
#include <vector>
#include <map>

class CDBTRule
{
public:
	typedef enum 
	{
		type_unknow,
		type_singal = 0,
		type_pairs,
		type_three,
		type_atom,
		type_boom,
		type_sister,
		type_threetwo,
		type_plane,

	}cards_type;

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
	static	int		getWeightNoRedFive(int card);
	static	bool	isNormal(const cards_type ty);


	static	bool	isSingle(const std::vector<int>& cards);
	static  bool	isPairs(const std::vector<int>& cards);
	static	bool	isthree(const std::vector<int>& cards);
	static	bool	isAtom(const std::vector<int>& cards);
	static	bool	isBoom(const std::vector<int>& cards);
	static	bool	isSister(const std::vector<int>& cards);
	static	bool	isPlane(const std::vector<int>& cards);
	static	bool	isThreetwo(const std::vector<int>& cards);

	static	std::pair<cards_type, int>	getType(const std::vector<int>& cards);
	static	bool	isBigger(const std::vector<int>& cards_per, const std::vector<int>& cards_now);
};
