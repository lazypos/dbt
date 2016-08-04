#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "HallScene.h"
#include "CommonFunction.h"
#include "MessageQueue.h"

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
	auto editBoxSize = Size(220, 50);

	//登录部分
	Sprite	*login = Sprite::create();
	login->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login"));
	login->setPosition(Vec2(visibleSize.width / 4, visibleSize.height-300));
	this->addChild(login);
	Sprite	*pass = Sprite::create();
	pass->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pass"));
	pass->setPosition(Vec2(visibleSize.width / 4, visibleSize.height - 380));
	this->addChild(pass);
	btlogin = ui::Button::create("login_bt.png", "login_bt_press.png", "login_bt_press.png");
	btlogin->setPosition(Vec2((visibleSize.width / 11) * 4, visibleSize.height - 460));
	btlogin->addTouchEventListener(CC_CALLBACK_2(CLoginScene::onLoginTouch, this));
	this->addChild(btlogin);
	//登录编辑框
	_editLoginName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editLoginName->setPosition(Vec2(login->getBoundingBox().getMaxX()- _editLoginName->getContentSize().width/2-5, login->getPosition().y));
	//_editLoginName->setPlaceHolder("UserName");
	_editLoginName->setText(Configuration::getInstance()->getValue("loginname").asString().c_str());
	_editLoginName->setFontColor(Color3B::BLACK);
	_editLoginName->setMaxLength(8);
	_editLoginName->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editLoginName);
	_editLoginPassword = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editLoginPassword->setPosition(Vec2(login->getBoundingBox().getMaxX() - _editLoginPassword->getContentSize().width / 2 - 5, pass->getPosition().y));
	_editLoginPassword->setFontColor(Color3B::BLACK);
	_editLoginPassword->setMaxLength(12);
	_editLoginPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editLoginPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editLoginPassword);
	//分割图
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
	btreg = ui::Button::create("reg_bt.png", "reg_bt_press.png", "reg_bt_press.png");
	btreg->setPosition(Vec2((visibleSize.width / 7) * 6, visibleSize.height - 520));
	btreg->addTouchEventListener(CC_CALLBACK_2(CLoginScene::onRegistTouch, this));
	this->addChild(btreg);
	//注册编辑框
	_editRegName = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editRegName->setPosition(Vec2(reglogin->getBoundingBox().getMaxX() - _editRegName->getContentSize().width / 2 - 5, reglogin->getPosition().y));
	_editRegName->setPlaceHolder(Configuration::getInstance()->getValue("login").asString().c_str());
	_editRegName->setFontColor(Color3B::BLACK);
	_editRegName->setMaxLength(8);
	_editRegName->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editRegName);
	_editRegNick = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editRegNick->setPosition(Vec2(regnick->getBoundingBox().getMaxX() - _editRegNick->getContentSize().width / 2 - 5, regnick->getPosition().y));
	_editRegNick->setPlaceHolder(Configuration::getInstance()->getValue("nick").asString().c_str());
	_editRegNick->setFontColor(Color3B::BLACK);
	_editRegNick->setMaxLength(5);
	_editRegNick->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editRegNick);
	_editRegPass = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editRegPass->setPosition(Vec2(regpass->getBoundingBox().getMaxX() - _editRegPass->getContentSize().width / 2 - 5, regpass->getPosition().y));
	_editRegPass->setPlaceHolder(Configuration::getInstance()->getValue("pass").asString().c_str());
	_editRegPass->setFontColor(Color3B::BLACK);
	_editRegPass->setMaxLength(12);
	_editRegPass->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editRegPass->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editRegPass);
	_editRegRepeatPass = ui::EditBox::create(editBoxSize, ui::Scale9Sprite::create());
	_editRegRepeatPass->setPosition(Vec2(regrpass->getBoundingBox().getMaxX() - _editRegRepeatPass->getContentSize().width / 2 - 5, regrpass->getPosition().y));
	_editRegRepeatPass->setPlaceHolder(Configuration::getInstance()->getValue("rpass").asString().c_str());
	_editRegRepeatPass->setFontColor(Color3B::BLACK);
	_editRegRepeatPass->setMaxLength(12);
	_editRegRepeatPass->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editRegRepeatPass->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	this->addChild(_editRegRepeatPass);
	
	this->scheduleUpdate();
	//注册观察者
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CLoginScene::ObserverLoginRegiste), "logn", nullptr);
    return true;
}

void CLoginScene::onLoginTouch(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bSend){
		//检查是否合法
		string user = _editLoginName->getText();
		string password = _editLoginPassword->getText();
		if (!checkUserIegal(user)){
			MessageBox("用户名只能用英文或者数字,长度在4-8个字符之间！", "提示");
			return;
		}
		if (!checkUserIegal(password)) {
			MessageBox("密码只允许用字母、符号、标点，请不要带特殊符号,长度在6-12个字符之间！", "提示");
			return;
		}
		char *rst = nullptr;
		base64Encode((unsigned char*)password.c_str(), password.length(), &rst);
		password = string(rst);
		free(rst);
		ostringstream os;
		os << "cmd=login;type=login;user=" << user
			<< ";pass=" << password;
		messageQueue::instance()->sendMessage(os.str());
#ifdef _DEBUG
// 		Scene *hall = CHallScene::createScene();
// 		Director::getInstance()->replaceScene(hall);
#endif
	}
}

void CLoginScene::onRegistTouch(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bSend) {
		string user = _editRegName->getText();
		string nick = _editRegNick->getText();
		string password = _editRegPass->getText();
		string rpass = _editRegRepeatPass->getText();
		if (!checkUserIegal(user)) {
			MessageBox("用户名只能用英文或者数字,长度在4-8个字符之间！", "提示");
			return;
		}
		if (!checkNickIegal(nick)) {
			MessageBox("昵称只能用不能用特殊字符,长度在5-10个字符之间！", "提示");
			return;
		}
		if (!checkPassIegal(password)) {
			MessageBox("密码只允许用字母、符号、标点，请不要带特殊符号,长度在6-12个字符之间！", "提示");
			return;
		}
		if (password != rpass) {
			MessageBox("两次密码输入不一致！", "提示");
			return;
		}

		char *rst = nullptr;
		base64Encode((unsigned char*)password.c_str(), password.length(), &rst);
		password = string(rst);
		free(rst);
		ostringstream os;
		os << "cmd=login;type=regist;user=" << user
			<< ";nick=" << nick
			<< ";pass=" << password;
		messageQueue::instance()->sendMessage(os.str());
	}
}

void CLoginScene::ObserverLoginRegiste(Ref* sendmsg)
{
	__String* p = (__String*)sendmsg;
	//解析字符串
	map<string, string> mapRst;
	stringToMap(p->_string, mapRst, ";");
	//登陆
	if (mapRst["type"] == "login"){
		if (mapRst["result"] == "ok") {
			//登陆成功，取消观察，场景切换(不能直接在此处切换)
			__NotificationCenter::getInstance()->removeObserver(this, "logn");
			replaceScene = true;
		}
		else
			MessageBox("用户名不存在或者密码错误！\r\n如果没有账号，请在右侧注册新账号。", "提醒");
	}
	//注册
	if (mapRst["type"] == "regist"){
		if (mapRst["result"] == "ok") {
			MessageBox("注册成功，请在左侧登陆游戏！", "提醒");
		}
		else
			MessageBox(mapRst["result"].c_str(), "提醒");
	}
	bSend = false;
}

void CLoginScene::update(float dt)
{
	if (replaceScene){
		Scene *hall = CHallScene::createScene();
		Director::getInstance()->replaceScene(hall);
	}
}

