#include "HallScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "DeskScene.h"
#include "MessageQueue.h"
#include "CommonFunction.h"

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

	Sprite *userMsg = Sprite::create();
	userMsg->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userMsg->setPosition(Vec2(visibleSize.width / 2- userMsg->getContentSize().width/2, visibleSize.height - userMsg->getContentSize().height/2));
	this->addChild(userMsg);
	Sprite *winMsg = Sprite::create();
	winMsg->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winMsg->setPosition(Vec2(visibleSize.width / 2+ winMsg->getContentSize().width / 2, visibleSize.height - winMsg->getContentSize().height/2));
	this->addChild(winMsg);

	//信息
	_nickName = Label::createWithTTF("player", "fonts/arial.ttf", 15);
	_nickName->setColor(Color3B::BLACK);
	_nickName->setAnchorPoint(Vec2(0, _nickName->getAnchorPoint().y));
	_nickName->setPosition(Vec2(visibleSize.width / 2 - 157, 
		visibleSize.height - userMsg->getContentSize().height/2));
	this->addChild(_nickName, 2);
	_score = Label::createWithTTF("10000", "fonts/arial.ttf", 15);
	_score->setColor(Color3B::BLACK);
	_score->setAnchorPoint(Vec2(0, _score->getAnchorPoint().y));
	_score->setPosition(Vec2(visibleSize.width / 2 - 56,
		visibleSize.height - userMsg->getContentSize().height / 2));
	this->addChild(_score, 2);
	_total = Label::createWithTTF("100", "fonts/arial.ttf", 15);
	_total->setColor(Color3B::BLACK);
	_total->setAnchorPoint(Vec2(0, _total->getAnchorPoint().y));
	_total->setPosition(Vec2(visibleSize.width / 2 + 50,
		visibleSize.height - userMsg->getContentSize().height / 2));
	this->addChild(_total, 2);
	_win = Label::createWithTTF("100%", "fonts/arial.ttf", 15);
	_win->setColor(Color3B::BLACK);
	_win->setAnchorPoint(Vec2(0, _win->getAnchorPoint().y));
	_win->setPosition(Vec2(visibleSize.width / 2 + 150,
		visibleSize.height - userMsg->getContentSize().height / 2));
	this->addChild(_win, 2);
	
	this->scheduleUpdate();
	//注册观察者
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CHallScene::ObserverAddDesk), "hall", nullptr);
	messageQueue::instance()->sendMessage("cmd=hall;type=getmsg");
    return true;
}

void CHallScene::OnFindDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		string deskNum = _editDesk->getText();
		if (atoi(_editDesk->getText()) == 0) {
			cocos2d::MessageBox("桌号只能是大于0的数字！", "Warning");
			return;
		}
		//发送
		if (messageQueue::instance()->sendMessage("cmd=hall;type=find;num="+deskNum))
			bsend = true;
	}
}

void CHallScene::OnCreateDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		//发送
		if (messageQueue::instance()->sendMessage("cmd=hall;type=create"))
			bsend = true;
	}
}

void CHallScene::OnFastAddDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		//发送
		if (messageQueue::instance()->sendMessage("cmd=hall;type=add"))
			bsend = true;
#ifdef _DEBUG
		Scene *scene = CDeskScene::createScene();
		Director::getInstance()->replaceScene(scene);
#endif
	}
}

void CHallScene::ObserverAddDesk(Ref* sendmsg)
{
	__String* p = (__String*)sendmsg;
	map<string, string> mapRst;
	stringToMap(p->_string, mapRst, ";");
	if (mapRst["type"] == "getmsg") {
		//设置信息
		_nickName->setString(mapRst["user"]);
		_score->setString(mapRst["score"]);
		_total->setString(mapRst["total"]);
		_win->setString(mapRst["win"]);
	}
	if (mapRst["type"] == "adddesk") {
		if (mapRst["result"] == "ok") {
			//加入桌子成功，取消观察，场景切换
			__NotificationCenter::getInstance()->removeObserver(this, "hall");
			changeScene = true;
			return;
		}
		bsend = false;
		if (mapRst["result"] == "full") {
			MessageBox("该桌号已满, 加入其它桌号。", "提示");
			return;
		}
		MessageBox("该桌号不存在, 加入其它桌号。", "提示");
		return;
	}
}

void CHallScene::update(float delta)
{
	if (changeScene){
		Scene *scene = CDeskScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
