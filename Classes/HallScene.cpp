#include "HallScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"

USING_NS_CC;

Scene* CHallScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CHallScene::create();
	scene->addChild(layer);
    return scene;
}

bool CHallScene::init()
{
    if (!Layer::init())
        return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *addDesk = Sprite::create();
	addDesk->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("add_desk_bg"));
	addDesk->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) + 60));
	this->addChild(addDesk, 1);
	btFindAdd = ui::Button::create("add_desk.png", "add_desk_press.png", "add_desk_press.png");
	btFindAdd->setPosition(Vec2(addDesk->getBoundingBox().getMaxX()- btFindAdd->getContentSize().width/2 - 5, (visibleSize.height / 2) + 60));
	btFindAdd->addTouchEventListener(CC_CALLBACK_2(CHallScene::OnFindDesk, this));
	this->addChild(btFindAdd,2);

	btCreadAdd = ui::Button::create("create_desk.png", "create_desk_press.png", "create_desk_press.png");
	btCreadAdd->setAnchorPoint(Vec2(0, 0));
	btCreadAdd->setPosition(Vec2(addDesk->getBoundingBox().getMinX(), (visibleSize.height / 2) - 60));
	btCreadAdd->addTouchEventListener(CC_CALLBACK_2(CHallScene::OnCreateDesk, this));
	this->addChild(btCreadAdd);

	btFastAdd = ui::Button::create("add_desk_fast.png", "add_desk_fast_press.png", "add_desk_fast_press.png");
	btFastAdd->setAnchorPoint(Vec2(0,0));
	btFastAdd->setPosition(Vec2(addDesk->getBoundingBox().getMaxX()-btFastAdd->getContentSize().width, (visibleSize.height / 2) - 60));
	btFastAdd->addTouchEventListener(CC_CALLBACK_2(CHallScene::OnFastAddDesk, this));
	this->addChild(btFastAdd);

	_editDesk = ui::EditBox::create(Size(192,46), ui::Scale9Sprite::create());
	_editDesk->setPosition(Vec2(addDesk->getBoundingBox().getMinX() + _editDesk->getContentSize().width / 2 + 5, addDesk->getPosition().y));
	_editDesk->setPlaceHolder(Configuration::getInstance()->getValue("desk").asString().c_str());
	_editDesk->setFontColor(Color3B::BLACK);
	_editDesk->setMaxLength(4);
	_editDesk->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	_editDesk->setInputMode(ui::EditBox::InputMode::NUMERIC);
	this->addChild(_editDesk,2);

    return true;
}

void CHallScene::OnFindDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (atoi(_editDesk->getText()) == 0)
			cocos2d::MessageBox("桌号只能是大于0的数字！", "Warning");
	}
}

void CHallScene::OnCreateDesk(Ref *pSender, ui::Widget::TouchEventType type)
{

}

void CHallScene::OnFastAddDesk(Ref *pSender, ui::Widget::TouchEventType type)
{

}
