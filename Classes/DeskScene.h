#ifndef __CDeskScene_H__
#define __CDeskScene_H__

#include "cocos2d.h"
#include "UI/UIButton.h"
#include "CardSprite.h"
USING_NS_CC;

typedef struct
{
	Vec2 nick;
	Vec2 win;
	Vec2 surplus;
	vector<CardSprite*> perCards;

}st_player_info;

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
private:
	ui::Button* _btReturn;
	ui::Button* _btReady;
	ui::Button* _btNoput;
	ui::Button* _btPut;

	bool		_isSatrting = false;
	bool		_isExit = false;

	vector<CardSprite*>		_lstCards;
	CardSprite* card_per =	nullptr;
	vector<st_player_info>	_vecPlayers;
	vector<int>				_vecPerCards;
};

#endif // __HELLOWORLD_SCENE_H__
