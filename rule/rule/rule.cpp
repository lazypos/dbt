// rule.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "DBTRule.h"
using namespace std;

int main()
{
	std::array<int, 216> arr;
	CDBTRule::shuffleCards(arr, 2);
	vector<int> v1, v2;
	v1.push_back(36);
	v1.push_back(36);
	v1.push_back(12);
	v1.push_back(51);
	v1.push_back(18);
	cout << CDBTRule::isBigger(v1, v2) << CDBTRule::getScore(v1) << endl;

    return 0;
}

