#ifndef __CHallScene_H__
#define __CHallScene_H__

#include "cocos2d.h"
#include "UI/UIEditBox/UIEditBox.h"
#include "UI/UIButton.h"
USING_NS_CC;

class CHallScene : public cocos2d::Layer, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(CHallScene);

	void OnFindDesk(Ref *pSender, ui::Widget::TouchEventType type);
	void OnCreateDesk(Ref *pSender, ui::Widget::TouchEventType type);
	void OnFastAddDesk(Ref *pSender, ui::Widget::TouchEventType type);

	void editBoxReturn(ui::EditBox* editBox) {};
	void ObserverAddDesk(Ref* sendmsg);

	void update(float delta);
private:
	ui::EditBox *_editDesk;
	ui::Button* btCreadAdd;
	ui::Button* btFastAdd;
	ui::Button* btFindAdd;
	bool		bsend = false;
	bool		changeScene = false;

	LabelTTF* _nickName;
	LabelTTF* _score;
	LabelTTF* _total;
	LabelTTF* _win;
};

#endif // __HELLOWORLD_SCENE_H__
