// rule.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "DBTRule.h"
using namespace std;

int main()
{
	std::array<int, 216> arr;
	CDBTRule::shuffleCards(arr, 2);

	cout << CDBTRule::getWeight(1) << endl;
	cout << CDBTRule::getWeight(53) << endl;
	cout << CDBTRule::getWeight(2) << endl;
	cout << CDBTRule::getWeight(4) << endl;
	cout << CDBTRule::getWeight(19) << endl;
    return 0;
}

