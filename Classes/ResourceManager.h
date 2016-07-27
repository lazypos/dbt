#ifndef  _CRESOURCEMANAGER_H_
#define  _CRESOURCEMANAGER_H_

#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;
using namespace std;

class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	void	loadResource();

private:
	void	loadCardResource();
};

typedef CSingleton<CResourceManager>	resourceMgr;
#endif