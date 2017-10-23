#pragma once

#include "cocos2d.h"


using namespace cocos2d;
class TouchScene : public::Layer
{
public:
    static ::Scene* createScene();
    Sprite * paddle1;
    virtual bool init();  

    virtual bool onTouchBegan(Touch*, Event*);
    virtual void onTouchEnded(Touch*, Event*);
    virtual void onTouchMoved(Touch*, Event*);
    virtual void onTouchCancelled(Touch*, Event*);
    CREATE_FUNC(TouchScene);

private:
};
