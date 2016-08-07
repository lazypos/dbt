#include "DeskScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "ResourceManager.h"
#include "ui/UIButton.h"
#include "HallScene.h"
#include "MessageQueue.h"
#include "DBTRule.h"
#include "CommonFunction.h"

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

	_btReturn = ui::Button::create("return.png", "return_press.png", "return_press.png");
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
	_btPut->setPosition(Vec2(visibleSize.width / 2 - 100, 170));
	_btPut->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onPut, this));
	_btPut->setScale(float(0.8));
	_btPut->setVisible(false);
	this->addChild(_btPut,2);
	_btNoput = ui::Button::create("noput.png", "noput_press.png", "noput_press.png");
	_btNoput->setPosition(Vec2(visibleSize.width / 2 + 100, 170));
	_btNoput->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onNoput, this));
	_btNoput->setScale(float(0.8));
	_btNoput->setVisible(false);
	this->addChild(_btNoput,2);
	_btReady = ui::Button::create("ready.png", "ready_press.png", "ready_press.png");
	_btReady->setPosition(Vec2(visibleSize.width / 2, 170));
	_btReady->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onReady, this));
	_btReady->setScale(float(0.8));
	_btReady->setVisible(true);
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

	//桌号
	_labelDeskNum = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	_labelDeskNum->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_labelDeskNum);
	_labelWeScore = Label::createWithTTF("0", "fonts/arial.ttf", 25);
	_labelWeScore->setPosition(Vec2(80, visibleSize.height - score->getContentSize().height / 2));
	_labelWeScore->setColor(Color3B::BLACK);
	this->addChild(_labelWeScore);
	_labelTheyScore = Label::createWithTTF("0", "fonts/arial.ttf", 25);
	_labelTheyScore->setPosition(Vec2(170, visibleSize.height - score->getContentSize().height / 2));
	_labelTheyScore->setColor(Color3B::BLACK);
	this->addChild(_labelTheyScore);

	//四个人->自己
	playerPtr ptr = make_shared<st_player_info>();
	ptr->_nickName = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_nickName->setPosition(Vec2(visibleSize.width / 2 - 135,
		userInfo0->getContentSize().height / 2));
	ptr->_nickName->setColor(Color3B::BLACK);
	this->addChild(ptr->_nickName,3);
	ptr->_score = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_score->setPosition(Vec2(visibleSize.width / 2 - 40,
		userInfo0->getContentSize().height / 2));
	ptr->_score->setColor(Color3B::BLACK);
	this->addChild(ptr->_score,3);
	ptr->_total = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_total->setPosition(Vec2(visibleSize.width / 2 + 60,
		userInfo0->getContentSize().height / 2));
	ptr->_total->setColor(Color3B::BLACK);
	this->addChild(ptr->_total,3);
	ptr->_win = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_win->setPosition(Vec2(visibleSize.width / 2 + 165,
		userInfo0->getContentSize().height / 2));
	ptr->_win->setColor(Color3B::BLACK);
	this->addChild(ptr->_win, 3);
	ptr->_surplus = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_surplus->setVisible(false);
	this->addChild(ptr->_surplus);
	ptr->_time = LabelAtlas::create("30", "num.png", 14, 21, '0');
	ptr->_time->setPosition(Vec2(visibleSize.width / 2 + 300, 200));
	ptr->_time->setVisible(false);
	this->addChild(ptr->_time);
	ptr->_ready = Sprite::create();
	ptr->_ready->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhunbei"));
	ptr->_ready->setPosition(Vec2(visibleSize.width / 2, 
		(visibleSize.height / 2) - 200));
	ptr->_ready->setVisible(false);
	this->addChild(ptr->_ready);
	ptr->_gone = LabelAtlas::create("0", "num.png", 14, 21, '0');
	ptr->_gone->setPosition(Vec2(visibleSize.width / 2 + 300, 200));
	ptr->_gone->setVisible(false);
	this->addChild(ptr->_gone);
	ptr->_x = visibleSize.width / 2 - 200;
	ptr->_y = 250;
	_vecPlayers.push_back(ptr);
	//->下家
	ptr = make_shared<st_player_info>();
	ptr->_nickName = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_nickName->setPosition(Vec2(visibleSize.width - 135,
		userInfo1->getPosition().y));
	ptr->_nickName->setColor(Color3B::BLACK);
	this->addChild(ptr->_nickName);
	ptr->_score = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_score->setPosition(Vec2(visibleSize.width - 40,
		userInfo1->getPosition().y));
	ptr->_score->setColor(Color3B::BLACK);
	this->addChild(ptr->_score);
	ptr->_total = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_total->setPosition(Vec2(visibleSize.width - 135,
		winInfo1->getPosition().y));
	ptr->_total->setColor(Color3B::BLACK);
	this->addChild(ptr->_total);
	ptr->_win = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_win->setPosition(Vec2(visibleSize.width - 40,
		winInfo1->getPosition().y));
	ptr->_win->setColor(Color3B::BLACK);
	this->addChild(ptr->_win);
	ptr->_surplus = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_surplus->setPosition(Vec2(visibleSize.width - 135,
		surplus1->getPosition().y));
	ptr->_surplus->setColor(Color3B::BLACK);
	this->addChild(ptr->_surplus);
	ptr->_time = LabelAtlas::create("30", "num.png", 14, 21, '0');
	ptr->_time->setPosition(Vec2(visibleSize.width / 2 + 260, 600));
	ptr->_time->setVisible(false);
	this->addChild(ptr->_time);
	ptr->_ready = Sprite::create();
	ptr->_ready->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhunbei"));
	ptr->_ready->setPosition(Vec2(visibleSize.width / 2+350,
		(visibleSize.height / 2)));
	ptr->_ready->setVisible(false);
	this->addChild(ptr->_ready);
	ptr->_gone = LabelAtlas::create("0", "num.png", 14, 21, '0');
	ptr->_gone->setPosition(Vec2(visibleSize.width / 2 + 260, 600));
	ptr->_gone->setVisible(false);
	this->addChild(ptr->_gone);
	ptr->_x = visibleSize.width / 2;
	ptr->_y = visibleSize.height / 2;
	_vecPlayers.push_back(ptr);
	//对家
	ptr = make_shared<st_player_info>();
	ptr->_nickName = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_nickName->setPosition(Vec2(visibleSize.width / 2 - 135,
		userInfo3->getPosition().y));
	ptr->_nickName->setColor(Color3B::BLACK);
	this->addChild(ptr->_nickName);
	ptr->_score = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_score->setPosition(Vec2(visibleSize.width / 2 - 40,
		userInfo3->getPosition().y));
	ptr->_score->setColor(Color3B::BLACK);
	this->addChild(ptr->_score);
	ptr->_total = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_total->setPosition(Vec2(visibleSize.width /2 + 60,
		winInfo3->getPosition().y));
	ptr->_total->setColor(Color3B::BLACK);
	this->addChild(ptr->_total);
	ptr->_win = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_win->setPosition(Vec2(visibleSize.width /2 + 165,
		winInfo3->getPosition().y));
	ptr->_win->setColor(Color3B::BLACK);
	this->addChild(ptr->_win);
	ptr->_surplus = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_surplus->setPosition(Vec2(visibleSize.width /2 - 35,
		surplus3->getPosition().y));
	ptr->_surplus->setColor(Color3B::BLACK);
	this->addChild(ptr->_surplus);
	ptr->_time = LabelAtlas::create("30", "num.png", 14, 21, '0');
	ptr->_time->setPosition(Vec2(visibleSize.width / 2 + 140, 
		surplus3->getPosition().y - 20));
	ptr->_time->setVisible(false);
	this->addChild(ptr->_time);
	ptr->_ready = Sprite::create();
	ptr->_ready->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhunbei"));
	ptr->_ready->setPosition(Vec2(visibleSize.width / 2,
		(visibleSize.height / 2) + 200));
	ptr->_ready->setVisible(false);
	this->addChild(ptr->_ready);
	ptr->_gone = LabelAtlas::create("0", "num.png", 14, 21, '0');
	ptr->_gone->setPosition(Vec2(visibleSize.width / 2 + 140,
		surplus3->getPosition().y - 20));
	ptr->_gone->setVisible(false);
	this->addChild(ptr->_gone);
	ptr->_x = visibleSize.width / 2 - 200;
	ptr->_y = visibleSize.height / 2 + 200;
	_vecPlayers.push_back(ptr);
	//上家
	ptr = make_shared<st_player_info>();
	ptr->_nickName = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_nickName->setPosition(Vec2(70,
		userInfo1->getPosition().y));
	ptr->_nickName->setColor(Color3B::BLACK);
	this->addChild(ptr->_nickName);
	ptr->_score = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_score->setPosition(Vec2(160,
		userInfo1->getPosition().y));
	ptr->_score->setColor(Color3B::BLACK);
	this->addChild(ptr->_score);
	ptr->_total = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_total->setPosition(Vec2(70,
		winInfo1->getPosition().y));
	ptr->_total->setColor(Color3B::BLACK);
	this->addChild(ptr->_total);
	ptr->_win = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_win->setPosition(Vec2(160,
		winInfo1->getPosition().y));
	ptr->_win->setColor(Color3B::BLACK);
	this->addChild(ptr->_win);
	ptr->_surplus = Label::createWithTTF("", "fonts/arial.ttf", 15);
	ptr->_surplus->setPosition(Vec2(70,
		surplus1->getPosition().y));
	ptr->_surplus->setColor(Color3B::BLACK);
	this->addChild(ptr->_surplus);
	ptr->_time = LabelAtlas::create("30", "num.png", 14, 21, '0');
	ptr->_time->setPosition(Vec2(visibleSize.width / 2 - 280, 600));
	ptr->_time->setVisible(false);
	this->addChild(ptr->_time);
	ptr->_ready = Sprite::create();
	ptr->_ready->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("zhunbei"));
	ptr->_ready->setPosition(Vec2(visibleSize.width / 2-350,
		visibleSize.height / 2));
	ptr->_ready->setVisible(false);
	this->addChild(ptr->_ready);
	ptr->_gone = LabelAtlas::create("0", "num.png", 14, 21, '0');
	ptr->_gone->setPosition(Vec2(visibleSize.width / 2 - 280, 600));
	ptr->_gone->setVisible(false);
	this->addChild(ptr->_gone);
	ptr->_x = 0;
	ptr->_y = visibleSize.height / 2;
	_vecPlayers.push_back(ptr);

	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(CDeskScene::playerSchedule), 1.0);
	//注册触摸事件
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CDeskScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CDeskScene::onTouchMoved, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CDeskScene::ObserverPlaying), "desk", nullptr);
	messageQueue::instance()->sendMessage("cmd=desk;type=getmsg");
    return true;
}

void CDeskScene::onReady(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (messageQueue::instance()->sendMessage("cmd=desk;type=ready")){
			_btReady->setVisible(false);
			_mapPlayers[_seatNum]->_ready->setVisible(true);
		}
	}
}

void CDeskScene::onReturn(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (_isSatrting && !_isExit){
			MessageBox("游戏还未结束，真的要退出吗？再次点击返回按钮将强制退出回到大厅！","提醒");
			_isExit = true;
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
		_btNoput->setVisible(false);
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
			_btNoput->setVisible(false);
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
	//一开始的手牌
	if (_recvtype == recv_start){
		_recvtype = 0;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		for (size_t i = 0; i < _vecStartCards.size(); i++) {
			auto cardSprite = CardSprite::createCardSprite(_vecStartCards[i]);
			cardSprite->setPosition(Vec2(visibleSize.width / 2 - (_vecStartCards.size()-1) * DEF_cardsep / 2 + i * DEF_cardsep + cardSprite->getContentSize().width / 4,
				45));
			this->addChild(cardSprite, 1);
			_lstCards.push_back(cardSprite);
		}
	}
	//重新整理手牌
	if (_recvtype == recv_review){
		_recvtype = 0;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		int i = 0;
		for (auto &it : _lstCards){
			it->setPosition(Vec2(visibleSize.width / 2 - (_lstCards.size() - 1) * DEF_cardsep / 2 + i * DEF_cardsep + it->getContentSize().width / 4,
				45));
			i++;
		}
	}
	//上一次出牌
	if (_perptr){
		int i = 0;
		for (auto it:_vecPerCards){
			auto cardSprite = CardSprite::createCardSprite(it);
			cardSprite->setPosition(Vec2(_perptr->_x+cardSprite->getContentSize().width + i*DEF_cardsep,
				_perptr->_y));
			_perptr->perCards.push_back(cardSprite);
			this->addChild(cardSprite);
			i++;
			//如果是自己，整理手牌
			if (_perptr->id == _seatNum) {
				auto itper = _lstCards.begin();
				while (itper != _lstCards.end()) {
					if ((*itper)->getSeq() == it){
						this->removeChild(*itper);
						_lstCards.erase(itper);
						break;
					}
					++itper;
				}
				_recvtype = recv_review;
			}
		}
		_perptr = nullptr;
	}
	if (_clear){
		_clear = false;
		for (auto it : _mapPlayers) {
			for (auto iit : it.second->perCards)
				this->removeChild(iit);
		}
	}
	if (_over){
		_over = false;
		_vecPerCards.clear();
		_timenow = nullptr;
		_mustput = false;
		_labelWeScore->setString("0");
		_labelTheyScore->setString("0");
		_btReady->setVisible(true);
		for (auto &it : _lstCards)
			this->removeChild(it);
		for (auto &it : _mapPlayers) {
			it.second->_gone->setVisible(false);
			it.second->_surplus->setString("0");
		}
	}
}


void CDeskScene::playerSchedule(float dt)
{
	//倒计时
	if (_timenow) {
		int t = atoi(_timenow->getString().c_str());
		t--;
		if (t >= 0) {
			ostringstream os;
			os << t;
			_timenow->setString(os.str());
			if (t == 0) { //如果是自己的
				_timenow->setVisible(false);
				for (auto it : _mapPlayers) {
					if (it.second->_time == _timenow && it.first == _seatNum) {
						if (_mustput) {//强制出牌
							_btPut->setVisible(false);
							_btNoput->setVisible(false);
							ostringstream os;
							os << "cmd=desk;type=put;cards=" << _lstCards[0]->getSeq();
							messageQueue::instance()->sendMessage(os.str());
						}
						else {
							_btPut->setVisible(false);
							_btNoput->setVisible(false);
							messageQueue::instance()->sendMessage("cmd=desk;type=noput");
						}
					}
				}
			}
		}
	}
}


void CDeskScene::ObserverPlaying(Ref* sendmsg)
{
	__String* p = (__String*)sendmsg;
	map<string, string> mapRst;
	stringToMap(p->_string, mapRst, ";");
	//获取信息
	if (mapRst["type"] == "getmsg"){
		auto it = mapRst.find("desknum");//桌号
		if (it != mapRst.end())
			_labelDeskNum->setString(it->second);
		it = mapRst.find("id");
		if (it != mapRst.end()) {//自己的座位号
			_seatNum = atoi(it->second.c_str());
			int i = _seatNum;
			for (auto &it : _vecPlayers) {
				_mapPlayers[i%4] = it;
				it->id = i % 4;
				i++;
			}
		}
		string players = mapRst["player"];
		//当前桌子上的人员信息
		if (players.length() > 0){
			list<string> tmp;
			stringToList(players, tmp, "|");
			for (const auto& it : tmp)
				playerAdd(it);
		}
	}
	//游戏
	if (mapRst["type"] == "play"){
		playerPtr ptr = _mapPlayers[atoi(mapRst["id"].c_str())];
		//准备
		if (mapRst["state"] == "ready"){
			ptr->_ready->setVisible(true);
		}
		//游戏开始
		else if (mapRst["state"] == "start") {
			_isSatrting = true;
			_btReady->setVisible(false);
			for (const auto&it : _mapPlayers) {
				it.second->_surplus->setString("54");
				it.second->_ready->setVisible(false);
			}
			vector<string> ctmp;
			stringToVector(mapRst["cards"], ctmp, ",");
			for (auto it : ctmp)
				_vecStartCards.push_back(atoi(it.c_str()));
			sort(_vecStartCards.begin(), _vecStartCards.end());
			_recvtype = recv_start;
			//谁出牌
			int putid = atoi(mapRst["now"].c_str());
			putCard(putid, true);
		}
		//玩家离开
		else if (mapRst["state"] == "leave") {
			playerLeave(ptr);
		}
		//玩家加入
		else if (mapRst["state"] == "add"){
			playerAdd(mapRst["player"]);
		}
		//玩家出牌/不出
		else if (mapRst["state"] == "put"){
			string cards = mapRst["cards"];
			int perid = atoi(mapRst["per"].c_str());
			int putid = atoi(mapRst["now"].c_str());
			int surplus = atoi(mapRst["surplus"].c_str());
			putPerCard(perid, cards, surplus, mapRst["go"]);
			if (putid != -1)
				putCard(putid, mapRst["clear"] == "1");
		}
		//玩家得分
		else if (mapRst["state"] == "score"){
			if (_seatNum % 2 == 0) {
				_labelWeScore->setString(mapRst["0"]);
				_labelTheyScore->setString(mapRst["1"]);
			}
			else {
				_labelWeScore->setString(mapRst["1"]);
				_labelTheyScore->setString(mapRst["0"]);
			}
		}
		//游戏结束
		else if (mapRst["state"] == "over"){
			//把一些状态清空
			_isSatrting = false;
			_card_select_per = nullptr;
			_isExit = false;
			updateScore(0, atoi(mapRst["s0"].c_str()));
			updateScore(1, atoi(mapRst["s1"].c_str()));
			updateScore(2, atoi(mapRst["s2"].c_str()));
			updateScore(3, atoi(mapRst["s3"].c_str()));
			ostringstream os;
			os << mapRst["n0"] << " " << mapRst["s0"] << "\r\n"
				<< mapRst["n1"] << " " << mapRst["s1"] << "\r\n"
				<< mapRst["n2"] << " " << mapRst["s2"] << "\r\n"
				<< mapRst["n3"] << " " << mapRst["s3"] << "\r\n";
			MessageBox(os.str().c_str(),"游戏结束");
			_over = true;
			_clear = true;
		}
	}
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

void CDeskScene::playerLeave(playerPtr ptr)
{
	ptr->_nickName->setString("");
	ptr->_score->setString("");
	ptr->_total->setString("");
	ptr->_win->setString("");
	ptr->_time->setVisible(false);
	ptr->_ready->setVisible(false);
}

void CDeskScene::playerAdd(const string& content)
{
	vector<string> vectmp;
	stringToVector(content, vectmp, "<>");
	playerPtr ptr = _mapPlayers[atoi(vectmp[0].c_str())];
	ptr->_nickName->setString(vectmp[1]);
	ptr->_score->setString(vectmp[2]);
	ptr->_total->setString(vectmp[3]);
	ptr->_win->setString(vectmp[4]);
	if (vectmp[5] == "1")
		ptr->_ready->setVisible(true);
	else
		ptr->_ready->setVisible(false);
}

void CDeskScene::putPerCard(int id, const string& cards, int surplus, const string& go)
{
	//处理上一家的状态
	if (id == _seatNum){
		_btPut->setVisible(false);
		_btNoput->setVisible(false);
	}
	playerPtr perptr = _mapPlayers[id];
	ostringstream os;
	os << surplus;
	perptr->_surplus->setString(os.str());
	perptr->_time->setVisible(false);
	perptr->perCards.clear();
	_vecPerCards.clear();
	for (auto &it : perptr->perCards)
		this->removeChild(it);
	if (!cards.empty()) {
		vector<string> vec1;
		stringToVector(cards, vec1, ",");
		int i = 0;
		for (const auto &it : vec1) {
			int seq = atoi(it.c_str());
			_vecPerCards.push_back(seq);
			i++;
		}
		sort(_vecPerCards.begin(), _vecPerCards.end());
		_perptr = perptr;
	}
	//出完了
	if (surplus == 0 && !go.empty()){
		perptr->_gone->setString(go);
		perptr->_gone->setVisible(true);
	}
}

void CDeskScene::putCard(int id, bool isclear /*= false*/)
{
	_putId = id;
	if (id == _seatNum) {
		_btPut->setVisible(true);
		_btNoput->setVisible(true);
	}
	playerPtr ptr = _mapPlayers[id];
	ptr->_time->setString("30");
	ptr->_time->setVisible(true);
	_timenow = ptr->_time;
	if (isclear){
		_clear = true;
	}
}

void CDeskScene::updateScore(int id, int score)
{
	playerPtr ptr = _mapPlayers[id];
	int s = atoi(ptr->_score->getString().c_str());
	s += score;
	ostringstream os;
	os << s;
	ptr->_score->setString(os.str());
}

bool CDeskScene::onTouchBegan(Touch *touch, Event *event)
{
	Point p = touch->getLocation();
	for (int i = _lstCards.size(); i > 0; i--) {
		CardSprite* card = _lstCards[i - 1];
		Rect recv = card->getBoundingBox();
		//位置太离谱的不处理
		if (p.y > recv.getMaxY() + 30)
			break;
		if (recv.containsPoint(p)) {
			_card_select_per = card;
			if (card->getSelect()) {
				card->setSelect(false);
				card->setPosition(Vec2(card->getPositionX(), 45));
			}
			else {
				card->setSelect(true);
				card->setPosition(Vec2(card->getPositionX(), 70));
			}
			break;
		}
	}
	return true;
}

void CDeskScene::onTouchMoved(Touch *touch, Event *event)
{
	Point p = touch->getLocation();
	Point per = touch->getPreviousLocation();

	for (size_t i = _lstCards.size(); i > 0; i--) {
		CardSprite* card = _lstCards[i - 1];
		Rect recv = card->getBoundingBox();
		if (p.y > recv.getMaxY() + 30)
			break;
		if (recv.containsPoint(p)) {
			//防止同一张牌颤抖
			if (card != _card_select_per) {
				_card_select_per = card;
				if (card->getSelect()) {
					card->setSelect(false);
					card->setPosition(Vec2(card->getPositionX(), 45));
				}
				else {
					card->setSelect(true);
					card->setPosition(Vec2(card->getPositionX(), 70));
				}
			}
			break;
		}
	}
}
