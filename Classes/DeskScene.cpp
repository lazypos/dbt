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

	//�����ĸ��˵���Ϣ
	Sprite* userInfo0 = Sprite::create();
	userInfo0->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nickname"));
	userInfo0->setPosition(Vec2(visibleSize.width / 2 - userInfo0->getContentSize().width / 2, userInfo0->getContentSize().height/2));
	this->addChild(userInfo0,2);
	Sprite* winInfo0 = Sprite::create();
	winInfo0->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win"));
	winInfo0->setPosition(Vec2(visibleSize.width / 2 + winInfo0->getContentSize().width / 2, winInfo0->getContentSize().height / 2));
	this->addChild(winInfo0,2);
	//���ư�ť
	_btPut = ui::Button::create("put.png", "put_press.png", "put_press.png");
	_btPut->setPosition(Vec2(visibleSize.width / 2 - 100, 145));
	_btPut->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onPut, this));
	_btPut->setScale(float(0.8));
	_btPut->setVisible(false);
	this->addChild(_btPut,2);
	_btNoput = ui::Button::create("noput.png", "noput_press.png", "noput_press.png");
	_btNoput->setPosition(Vec2(visibleSize.width / 2 + 100, 145));
	_btNoput->addTouchEventListener(CC_CALLBACK_2(CDeskScene::onNoput, this));
	_btNoput->setScale(float(0.8));
	_btNoput->setVisible(false);
	this->addChild(_btNoput,2);
	_btReady = ui::Button::create("ready.png", "ready_press.png", "ready_press.png");
	_btReady->setPosition(Vec2(visibleSize.width / 2, 145));
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

	//����
	_labelDeskNum = Label::createWithTTF("0", "fonts/arial.ttf", 20);
	_labelDeskNum->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_labelDeskNum);
	_labelWeScore = Label::createWithTTF("0", "fonts/arial.ttf", 25);
	_labelWeScore->setPosition(Vec2(60, visibleSize.height - score->getContentSize().height / 2));
	_labelWeScore->setColor(Color3B::BLACK);
	this->addChild(_labelWeScore);
	_labelTheyScore = Label::createWithTTF("0", "fonts/arial.ttf", 25);
	_labelTheyScore->setPosition(Vec2(160, visibleSize.height - score->getContentSize().height / 2));
	_labelTheyScore->setColor(Color3B::BLACK);
	this->addChild(_labelTheyScore);

	//�ĸ���->�Լ�
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
	_vecPlayers.push_back(ptr);
	//->�¼�
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
	_vecPlayers.push_back(ptr);
	//�Լ�
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
	_vecPlayers.push_back(ptr);
	//�ϼ�
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
	_vecPlayers.push_back(ptr);

	this->scheduleUpdate();
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(CDeskScene::ObserverPlaying), "desk", nullptr);
	messageQueue::instance()->sendMessage("cmd=desk;type=getmsg");
    return true;
}

void CDeskScene::onReady(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		messageQueue::instance()->sendMessage("cmd=desk;type=ready");
		_btReady->setVisible(false);
		_mapPlayers[_seatNum]->_ready->setVisible(true);
	}
}

void CDeskScene::onReturn(Ref *pSender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED) {
		if (_isSatrting && !_isExit){
			MessageBox("��Ϸ��δ���������Ҫ�˳����ٴε�����ذ�ť��ǿ���˳��ص�������","����");
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
		//��ʱ�����ã��Ƶ���һλ
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
			//��ʱ�����ã��Ƶ���һλ
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
	map<string, string> mapRst;
	stringToMap(p->_string, mapRst, ";");
	//��ȡ��Ϣ
	if (mapRst["type"] == "getmsg"){
		auto it = mapRst.find("desknum");//����
		if (it != mapRst.end())
			_labelDeskNum->setString(it->second);
		it = mapRst.find("id");
		if (it != mapRst.end()) {//�Լ�����λ��
			_seatNum = atoi(it->second.c_str());
			int i = _seatNum;
			for (auto &it : _vecPlayers) {
				_mapPlayers[i%4] = it;
				i++;
			}
		}
		string players = mapRst["player"];
		//��ǰ�����ϵ���Ա��Ϣ
		if (players.length() > 0){
			list<string> tmp;
			stringToList(players, tmp, "|");
			for (const auto& it : tmp)
				playerAdd(it);
		}
	}
	//��Ϸ
	if (mapRst["type"] == "play"){
		playerPtr ptr = _mapPlayers[atoi(mapRst["id"].c_str())];
		//׼��
		if (mapRst["state"] == "ready"){
			ptr->_ready->setVisible(true);
		}
		//��Ϸ��ʼ
		else if (mapRst["state"] == "start") {
			for (const auto&it : _mapPlayers) {
				it.second->_surplus->setString("54");
				it.second->_ready->setVisible(false);
			}
			vector<string> vecCards;
			stringToVector(mapRst["cards"], vecCards, ",");
			sort(vecCards.begin(), vecCards.end());
			auto visibleSize = Director::getInstance()->getVisibleSize();
			for (int i = 0; i < 54; i++) {
				auto cardSprite = CardSprite::createCardSprite(atoi(vecCards[i].c_str()));
				cardSprite->setPosition(Vec2(visibleSize.width / 2 - 53 * DEF_cardsep / 2 + i * DEF_cardsep + cardSprite->getContentSize().width / 4,
					cardSprite->getContentSize().height / 3));
				cardSprite->setTag(i);
				this->addChild(cardSprite, 1, cardSprite->getTag());
				_lstCards.push_back(cardSprite);
			}
		}
		//����뿪
		else if (mapRst["state"] == "leave") {
			playerLeave(ptr);
		}
		//��Ҽ���
		else if (mapRst["state"] == "add"){
			playerAdd(mapRst["player"]);
		}
		//��ҳ���/����
		else if (mapRst["state"] == "put"){
			string cards = mapRst["cards"];
			if (cards.empty()) {

			}
			else {
				
			}
		}
		//��ҵ÷�
		else if (mapRst["state"] == "score"){
			
		}
		//��Ϸ����
		else if (mapRst["state"] == "over"){

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
