#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include <UI/UIButton.h>
#include "DBTRule.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	resourceMgr::instance()->loadResource();

	for (int i=0; i<54; i++)
	{
		auto cardSprite = CardSprite::createCardSprite(i);
		cardSprite->setPosition(Vec2(60+i * 18, 100));
		cardSprite->setTag(i);
		this->addChild(cardSprite, 1, cardSprite->getTag());
		lstCards.push_back(cardSprite);
	}

// 	MenuItemImage *noputbtn = MenuItemImage::create();
// 	noputbtn->set
	ui::Button* noput = ui::Button::create("noput.png");
	noput->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchEvent, this));
	noput->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+100));
	this->addChild(noput);

	//注册触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//listener->setSwallowTouches(true);//不向下传递触摸
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	Point p = touch->getLocation();
	for (int i = lstCards.size(); i > 0; i--) {
		CardSprite* card = lstCards[i - 1];
		Rect recv = card->getBoundingBox();
		//位置太离谱的不处理
		if (p.y > recv.getMaxY() + 30)
			break;
		if (recv.containsPoint(p)) {
			card_per = card;
			if (card->getSelect()) {
				card->setSelect(false);
				card->setPosition(Vec2(card->getPositionX(), 100));
			}
			else {
				card->setSelect(true);
				card->setPosition(Vec2(card->getPositionX(), 130));
			}
			break;
		}
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
	Point p = touch->getLocation();
	Point per = touch->getPreviousLocation();

	for (int i = lstCards.size(); i > 0; i--) {
		CardSprite* card = lstCards[i - 1];
		Rect recv = card->getBoundingBox();
		if (p.y > recv.getMaxY() + 30)
			break;
		if (recv.containsPoint(p)) {
			//防止同一张牌颤抖
			if (card != card_per){ 
				card_per = card;
				if (card->getSelect()) {
					card->setSelect(false);
					card->setPosition(Vec2(card->getPositionX(), 100));
				}
				else {
					card->setSelect(true);
					card->setPosition(Vec2(card->getPositionX(), 130));
				}
			}
			break;
		}
	}
}

void HelloWorld::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type){
		vector<int> v;
		for (auto &it : lstCards)
			if (it->getSelect())
				v.push_back(it->getSeq());
		auto pt = CDBTRule::getType(v);
		if (pt.first == CDBTRule::type_unknow)
			MessageBox("dsadsa", "1");
		return;

		//是否有牌被选中
		bool bselected = false;
		for (auto &it : lstCards) {
			if (it->getSelect()) {
				bselected = true;
				break;
			}
		}
		if (!bselected)
			return;


		//先清理之前的牌
		for (auto &it : perCards)
			this->removeChildByTag(it->getTag());

		//出牌
		perCards.clear();
		auto it1 = lstCards.begin();
		while (it1 != lstCards.end()){
			if ((*it1)->getSelect()) {
				perCards.push_back(*it1);
				it1 = lstCards.erase(it1);
				if (it1 == lstCards.end())
					break;
			}else
				++it1;
		}
		int len = 120 + perCards.size() * 20;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		int beginPos = (visibleSize.width - len) / 2;
		int i = 0;
		for (const auto &it : perCards) {
			it->setPosition(Vec2(100 + i * 18, 700));
			i++;
		}
		//重新展示
		len = 120 + lstCards.size() * 20;
		beginPos = (visibleSize.width - len) / 2;
		for (auto it = lstCards.begin(); it != lstCards.end(); ++it) {
			int i = 0;
			for (const auto &it : lstCards) {
				it->setPosition(Vec2(beginPos+60 + i * 18, 100));
				i++;
			}
		}
	}
}

