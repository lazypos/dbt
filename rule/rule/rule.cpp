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
    return 0;
}

