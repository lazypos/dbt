#ifndef __CDeskScene_H__
#define __CDeskScene_H__

#include "cocos2d.h"
#include "UI/UIButton.h"
USING_NS_CC;

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

private:
	ui::Button* _btReady;
	ui::Button* _btReturn;
	ui::Button* _btNoput;
	ui::Button* _btPut;

	bool		_isSatrting = false;
	bool		_isExit = false;
};

#endif // __HELLOWORLD_SCENE_H__
