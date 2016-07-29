#ifndef __CLoginLayer_H__
#define __CLoginLayer_H__

#include "cocos2d.h"
#include "UI/UIEditBox/UIEditBox.h"
USING_NS_CC;

class CLoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(CLoginScene);

private:
	ui::EditBox *_editName;
	ui::EditBox *_editPassword;
	ui::EditBox *_editEmail;
};

#endif // __HELLOWORLD_SCENE_H__
