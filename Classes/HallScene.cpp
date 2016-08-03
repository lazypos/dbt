#include "HallScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "DeskScene.h"
#include "MessageQueue.h"

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

	//ע��۲���
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CHallScene::ObserverAddDesk), "hall", nullptr);

    return true;
}

void CHallScene::OnFindDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		string deskNum = _editDesk->getText();
		if (atoi(_editDesk->getText()) == 0) {
			cocos2d::MessageBox("����ֻ���Ǵ���0�����֣�", "Warning");
			return;
		}
		//����
		if (messageQueue::instance()->sendMessage("cmd=desk;type=find;num="+deskNum))
			bsend = true;
	}
}

void CHallScene::OnCreateDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		//����
		if (messageQueue::instance()->sendMessage("cmd=desk;type=create"))
			bsend = true;
	}
}

void CHallScene::OnFastAddDesk(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED && !bsend) {
		//����
		if (messageQueue::instance()->sendMessage("cmd=desk;type=add"))
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
	if (p->_string == "ok") {
		//�������ӳɹ���ȡ���۲죬�����л�
		__NotificationCenter::getInstance()->removeObserver(this, "hall");
		Scene *scene = CDeskScene::createScene();
		Director::getInstance()->replaceScene(scene);
		return;
	}
	bsend = false;
	if (p->_string == "full") {
		MessageBox("����������, �����������š�", "��ʾ");
		return;
	}
	MessageBox("�����Ų�����, �����������š�", "��ʾ");
	return;
}
