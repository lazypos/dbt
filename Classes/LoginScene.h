#ifndef __CLoginLayer_H__
#define __CLoginLayer_H__

#include "cocos2d.h"

class CLoginScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(CLoginScene);
};

#endif // __HELLOWORLD_SCENE_H__
