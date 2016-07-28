#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "UI/UIButton.h"
using namespace ui;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);

	void touchEvent(Ref *pSender, Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	vector<CardSprite*> lstCards;
	vector<CardSprite*> perCards;
	CardSprite* card_per = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
