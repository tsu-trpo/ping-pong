#pragma once
#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "cocos2d.h"


using namespace cocos2d;
class TouchScene : public::Layer
{
public:
    static::Scene* createScene();
    Paddle *paddle1;
    Ball *glob;
    Vector <Brick*> bricks_m;

    virtual bool init();

    virtual bool onTouchBegan(Touch*, Event*);
    virtual void onTouchEnded(Touch*, Event*);
    virtual void onTouchMoved(Touch*, Event*);
    virtual void onTouchCancelled(Touch*, Event*);
    CREATE_FUNC(TouchScene);

    void doStep(float delta);

private:
};
