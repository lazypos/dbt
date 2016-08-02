#ifndef __CLoginLayer_H__
#define __CLoginLayer_H__

#include "cocos2d.h"
#include "UI/UIEditBox/UIEditBox.h"
USING_NS_CC;

class CLoginScene : public cocos2d::Layer, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	CREATE_FUNC(CLoginScene);
   
protected:
	void onLoginTouch(Ref *pSender, ui::Widget::TouchEventType type);
	void onRegistTouch(Ref *pSender, ui::Widget::TouchEventType type);

	void editBoxReturn(ui::EditBox* editBox) {};

	void ObserverLoginRegiste(Ref* sendmsg);

private:
	ui::EditBox *_editLoginName;
	ui::EditBox *_editLoginPassword;
	ui::EditBox *_editRegName;
	ui::EditBox *_editRegNick;
	ui::EditBox *_editRegPass;
	ui::EditBox *_editRegRepeatPass;

	ui::Button* btlogin;
	ui::Button* btreg;

	bool	bSend = false;
};

#endif // __HELLOWORLD_SCENE_H__
