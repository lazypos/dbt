#include "DeskScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "HallScene.h"
#include "MessageQueue.h"
#include "DBTRule.h"

USING_NS_CC;

#define  DEF_cardsep 18

Scene* CDeskScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CDeskScene::create();
	scene->addChild(layer);
    return scene;
}

bool CDeskScene::init()
{
    if (!Layer::init())
        return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	_btReturn = ui::Button::create("add_desk.png", "add_desk_press.png", "add_desk_press.png");
	_btReturn->setPosition(Vec2(visibleSize.width - _btReturn->getContentSize().width / 2, 
		visibleSize.height - _btReturn->getContentSize().height / 2));
	_btReturn->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onReturn, this));
	this->addChild(_btReturn);

	Sprite* score = Sprite::create();
	score->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("score"));
	score->setPosition(Vec2(score->getContentSize().width / 2, visibleSize.height - score->getContentSize().height / 2));
	this->addChild(score);

	//加载四个人的信息
	Sprite* userInfo0 = Sprite::create();
	userInfo0->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userInfo0->setPosition(Vec2(visibleSize.width / 2 - userInfo0->getContentSize().width / 2, userInfo0->getContentSize().height/2));
	this->addChild(userInfo0,2);
	Sprite* winInfo0 = Sprite::create();
	winInfo0->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winInfo0->setPosition(Vec2(visibleSize.width / 2 + winInfo0->getContentSize().width / 2, winInfo0->getContentSize().height / 2));
	this->addChild(winInfo0,2);
	//出牌按钮
	_btPut = ui::Button::create("put.png", "put_press.png", "put_press.png");
	_btPut->setPosition(Vec2(visibleSize.width / 2 - 100, 150));
	_btPut->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onPut, this));
	_btPut->setScale(float(0.8));
	this->addChild(_btPut,2);
	_btNoput = ui::Button::create("noput.png", "noput_press.png", "noput_press.png");
	_btNoput->setPosition(Vec2(visibleSize.width / 2 + 100, 150));
	_btNoput->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onNoput, this));
	_btNoput->setScale(float(0.8));
	this->addChild(_btNoput,2);
	_btReady = ui::Button::create("ready.png", "ready_press.png", "ready_press.png");
	_btReady->setPosition(Vec2(visibleSize.width / 2, 150));
	_btReady->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onReady, this));
	_btReady->setScale(float(0.8));
	this->addChild(_btReady, 2);

	Sprite* userInfo1 = Sprite::create();
	userInfo1->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userInfo1->setPosition(Vec2(visibleSize.width - userInfo1->getContentSize().width / 2, 
		600 + userInfo1->getContentSize().height));
	this->addChild(userInfo1);
	Sprite* winInfo1 = Sprite::create();
	winInfo1->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winInfo1->setPosition(Vec2(visibleSize.width - winInfo1->getContentSize().width / 2, 
		600));
	this->addChild(winInfo1);
	Sprite* surplus1 = Sprite::create();
	surplus1->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("surplus"));
	surplus1->setPosition(Vec2(visibleSize.width - surplus1->getContentSize().width / 2,
		600 - surplus1->getContentSize().height));
	this->addChild(surplus1);

	Sprite* userInfo2 = Sprite::create();
	userInfo2->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userInfo2->setPosition(Vec2(userInfo2->getContentSize().width / 2,
		600 + userInfo2->getContentSize().height));
	this->addChild(userInfo2);
	Sprite* winInfo2 = Sprite::create();
	winInfo2->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winInfo2->setPosition(Vec2(winInfo2->getContentSize().width / 2, 
		600));
	this->addChild(winInfo2);
	Sprite* surplus2 = Sprite::create();
	surplus2->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("surplus"));
	surplus2->setPosition(Vec2(surplus2->getContentSize().width / 2,
		600 - surplus2->getContentSize().height));
	this->addChild(surplus2);

	Sprite* userInfo3 = Sprite::create();
	userInfo3->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userInfo3->setPosition(Vec2(visibleSize.width / 2 - userInfo3->getContentSize().width / 2,
		visibleSize.height - userInfo3->getContentSize().height / 2));
	this->addChild(userInfo3);
	Sprite* winInfo3 = Sprite::create();
	winInfo3->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winInfo3->setPosition(Vec2(visibleSize.width / 2 + userInfo3->getContentSize().width / 2,
		visibleSize.height - userInfo3->getContentSize().height / 2));
	this->addChild(winInfo3);
	Sprite* surplus3 = Sprite::create();
	surplus3->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("surplus"));
	surplus3->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height - surplus3->getContentSize().height*1.5));
	this->addChild(surplus3);

	for (int i = 0; i < 54; i++){
		auto cardSprite = CardSprite::createCardSprite(i);
		cardSprite->setPosition(Vec2(visibleSize.width / 2 - 53 * DEF_cardsep / 2 + i * DEF_cardsep + cardSprite->getContentSize().width/4, 
			cardSprite->getContentSize().height / 3));
		cardSprite->setTag(i);
		this->addChild(cardSprite, 1, cardSprite->getTag());
		_lstCards.push_back(cardSprite);
	}

	this->scheduleUpdate();
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CDeskScene::ObserverPlaying), "desk", nullptr);
    return true;
}

void CDeskScene::onReady(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		messageQueue::instance()->sendMessage("cmd=desk;type=ready");
		_btReady->setEnabled(false);
		_btReady->setVisible(false);
	}
}

void CDeskScene::onReturn(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (_isSatrting && !_isExit){
			MessageBox("游戏还未结束，真的要退出吗？再次点击返回按钮将强制退出回到大厅！","提醒");
			return;
		}
		messageQueue::instance()->sendMessage("cmd=desk;type=quit");
		Scene *hScene = CHallScene::createScene();
		Director::getInstance()->replaceScene(hScene);
	}
}

void CDeskScene::onNoput(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		_btPut->setVisible(false);
		_btPut->setEnabled(false);
		_btNoput->setVisible(false);
		_btNoput->setEnabled(false);
		messageQueue::instance()->sendMessage("cmd=desk;type=noput");
		//计时器重置，移到下一位
	}
}

void CDeskScene::onPut(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		vector<int> nowCards = getSelectCardList();
		if (CDBTRule::isBigger(_vecPerCards, nowCards)){
			_btPut->setVisible(false);
			_btPut->setEnabled(false);
			_btNoput->setVisible(false);
			_btNoput->setEnabled(false);
			ostringstream os;
			os << "cmd=desk;type=put;cards=";
			for (const auto &it : nowCards)
				os << it << ",";
			messageQueue::instance()->sendMessage(os.str());
			//计时器重置，移到下一位
			return;
		}
	}
}

void CDeskScene::update(float dt)
{
}

void CDeskScene::ObserverPlaying(Ref* sendmsg)
{
	__String* p = (__String*)sendmsg;
}

std::vector<int> CDeskScene::getSelectCardList()
{
	vector<int> vec;
	for_each(_lstCards.begin(), _lstCards.end(), [&vec](CardSprite* p) {
		if (p->getSelect())
			vec.push_back(p->getSeq());
	});
	sort(vec.begin(), vec.end());
	return vec;
}

