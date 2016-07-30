#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"

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

	//登录部分
	Sprite	*login = Sprite::create();
	login->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login"));
	login->setPosition(Vec2(visibleSize.width / 4, visibleSize.height-300));
	this->addChild(login);
	Sprite	*pass = Sprite::create();
	pass->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pass"));
	pass->setPosition(Vec2(visibleSize.width / 4, visibleSize.height - 380));
	this->addChild(pass);
	ui::Button* btlogin = ui::Button::create("login_bt.png", "login_bt_press.png", "login_bt_press.png");
	btlogin->setPosition(Vec2((visibleSize.width / 11) * 4, visibleSize.height - 460));
	this->addChild(btlogin);

	Sprite	*sep = Sprite::create();
	sep->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sep"));
	sep->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sep);

	//注册部分
	Sprite	*reglogin = Sprite::create();
	reglogin->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login"));
	reglogin->setPosition(Vec2((visibleSize.width / 4) * 3, visibleSize.height - 200));
	this->addChild(reglogin);
	Sprite	*regnick = Sprite::create();
	regnick->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nick"));
	regnick->setPosition(Vec2((visibleSize.width / 4) * 3, visibleSize.height - 280));
	this->addChild(regnick);
	Sprite	*regpass = Sprite::create();
	regpass->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pass"));
	regpass->setPosition(Vec2((visibleSize.width / 4) * 3, visibleSize.height - 360));
	this->addChild(regpass);
	Sprite	*regrpass = Sprite::create();
	regrpass->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rpass"));
	regrpass->setPosition(Vec2((visibleSize.width / 4) * 3, visibleSize.height - 440));
	this->addChild(regrpass);
	ui::Button* btreg = ui::Button::create("reg_bt.png", "reg_bt_press.png", "reg_bt_press.png");
	btreg->setPosition(Vec2((visibleSize.width / 7) * 6, visibleSize.height - 520));
	this->addChild(btreg);

    return true;
}

