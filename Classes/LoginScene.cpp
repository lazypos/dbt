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
    
// 	auto editBoxSize = Size(500, 50);
// 	_editName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create("noput.png"));
// 	_editName->setMaxLength(8);
// 	_editName->setPosition(Vec2(500, 500));
// 	this->addChild(_editName);

	ui::Button* bt = ui::Button::create("join_bt0.png", "join_bt1.png", "join_bt1.png");
	bt->setPosition(Vec2(500, 500));
	this->addChild(bt);
	ui::Button* bt1 = ui::Button::create("search.png", "search.png", "search.png");
	bt->setPosition(Vec2(0, 0));
	bt1->setAnchorPoint(Vec2(0,0));
	this->addChild(bt1);

    return true;
}

