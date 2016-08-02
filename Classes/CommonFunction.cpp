#include "CommonFunction.h"


bool checkUserIegal(const string& name)
{
	if (name.length() < 4 || name.length() > 8)
		return false;
	for (size_t i = 0; i < name.size(); ++i) {
		if (!isalpha(name[i]) && !isdigit(name[i]))
			return false;
	}
	return true;
}

bool checkPassIegal(const string& pass)
{
	if (pass.length() < 6 || pass.length() > 12)
		return false;
	for (size_t i = 0; i < pass.size(); ++i) {
		if (!isascii(pass[i]))
			return false;
	}
	return true;
}

bool checkNickIegal(const string& name)
{
	if (name.length() > 10 || name.length() < 4)
		return false;
	if (name.find(".") != string::npos
		|| name.find("'") != string::npos
		|| name.find("\"") != string::npos
		|| name.find("`") != string::npos
		|| name.find("*") != string::npos
		|| name.find("&") != string::npos
		|| name.find("!") != string::npos
		|| name.find("/") != string::npos
		|| name.find("\\") != string::npos)
		return false;
	return true;
}
