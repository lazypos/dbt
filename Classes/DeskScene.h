#ifndef __CDeskScene_H__
#define __CDeskScene_H__

#include "cocos2d.h"
#include "UI/UIButton.h"
#include "CardSprite.h"
#include <chrono>
USING_NS_CC;

typedef struct
{
	Label* _nickName;
	Label* _score;
	Label* _total;
	Label* _win;
	Label* _surplus;
	Sprite*_ready;
	LabelAtlas* _time;
	LabelAtlas* _gone;
	int 	_x;
	int		_y;
	int		id;
	chrono::time_point<chrono::system_clock> timepoint;
	vector<CardSprite*> perCards;

}st_player_info;
typedef shared_ptr<st_player_info> playerPtr;

bool inline mycompair(CardSprite* c1, CardSprite* c2) {
	return c1->getSeq() > c2->getSeq();
}

class CDeskScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(CDeskScene);

 	void onReady(Ref *pSender, ui::Widget::TouchEventType type);
	void onReturn(Ref *pSender, ui::Widget::TouchEventType type);
	void onNoput(Ref *pSender, ui::Widget::TouchEventType type);
	void onPut(Ref *pSender, ui::Widget::TouchEventType type);

	void update(float dt);
	void ObserverPlaying(Ref* sendmsg);
	vector<int>	getSelectCardList();

	void	playerLeave(playerPtr ptr);
	void	playerAdd(const string& content);
	void	putPerCard(int id, const string& cards, int surplus, const string& go="");
	void	putCard(int id, bool isclear = false);
	void	updateScore(int id, int score);

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);

	void    playerSchedule(float dt);

private:
	//static Scene	*_scene;
	ui::Button* _btReturn;
	ui::Button* _btReady;
	ui::Button* _btNoput; 
	ui::Button* _btPut;

	bool		_isSatrting = false;
	bool		_isExit = false;

	Label*	_labelDeskNum;
	Label*	_labelWeScore;
	Label*	_labelTheyScore;

	LabelAtlas*					_timenow = nullptr;
	bool						_mustput = false;

	vector<CardSprite*>			_lstCards; //自己的手牌
	CardSprite*					_card_select_per =	nullptr; 
	vector<playerPtr>			_vecPlayers; //初始化的时候放在这里，然后根据A的id插入到map里
	map<int, playerPtr>			_mapPlayers;
	vector<int>					_vecPerCards; //上一次出的牌
	playerPtr					_perptr = nullptr;
	int							_seatNum;
	int							_putId;

#define recv_start 1
#define recv_review 2
	vector<int>					_vecStartCards;
};

#endif // __HELLOWORLD_SCENE_H__
