#ifndef __CDeskScene_H__
#define __CDeskScene_H__

#include "cocos2d.h"
#include "UI/UIButton.h"
#include "CardSprite.h"
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
	vector<CardSprite*> perCards;

}st_player_info;
typedef shared_ptr<st_player_info> playerPtr;

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

private:
	ui::Button* _btReturn;
	ui::Button* _btReady;
	ui::Button* _btNoput;
	ui::Button* _btPut;

	bool		_isSatrting = false;
	bool		_isExit = false;

	Label*	_labelDeskNum;
	Label*	_labelWeScore;
	Label*	_labelTheyScore;

	vector<CardSprite*>			_lstCards;
	CardSprite*					_card_select_per =	nullptr;
	vector<playerPtr>			_vecPlayers; //初始化的时候放在这里，然后根据A的id插入到map里
	map<int, playerPtr>			_mapPlayers;
	vector<int>					_vecPerCards;
	int							_seatNum;
};

#endif // __HELLOWORLD_SCENE_H__
