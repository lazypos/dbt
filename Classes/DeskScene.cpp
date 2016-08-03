#include "DeskScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "HallScene.h"

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

	//�����ĸ��˵���Ϣ


	for (int i = 0; i < 54; i++){
		auto cardSprite = CardSprite::createCardSprite(i);
		cardSprite->setPosition(Vec2(visibleSize.width / 2 - 53 * DEF_cardsep / 2 + i * DEF_cardsep + cardSprite->getContentSize().width/4, 
			cardSprite->getContentSize().height / 2 + 45));
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

	}
}

void CDeskScene::onReturn(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (_isSatrting && !_isExit){
			MessageBox("��Ϸ��δ���������Ҫ�˳����ٴε�����ذ�ť��ǿ���˳��ص�������","����");
			return;
		}
		Scene *hScene = CHallScene::createScene();
		Director::getInstance()->replaceScene(hScene);
	}
}

void CDeskScene::onNoput(Ref *pSender, ui::Widget::TouchEventType type)
{

}

void CDeskScene::onPut(Ref *pSender, ui::Widget::TouchEventType type)
{

}

void CDeskScene::update(float dt)
{
}

void CDeskScene::ObserverPlaying(Ref* sendmsg)
{
	__String* p = (__String*)sendmsg;
}

