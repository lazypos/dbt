#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"

USING_NS_CC;

Scene* CLoginScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CLoginScene::create();
	scene->addChild(layer);
    return scene;
}

bool CLoginScene::init()
{
    if (!Layer::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	resourceMgr::instance()->loadResource();

	for (int i=0; i<54; i++)
	{
		auto cardSprite = CardSprite::createCardSprite(i);
		cardSprite->setPosition(Vec2(60+i * 18, 100));
		this->addChild(cardSprite, 1);
	}
    
    return true;
}

