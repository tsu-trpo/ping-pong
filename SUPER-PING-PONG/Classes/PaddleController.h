#pragma once
#include "cocos2d.h"
#include "Paddle.h"

class Paddle;

using namespace cocos2d;

class PaddleController : public Layer
{
    Paddle* _paddle;
    EventListenerTouchOneByOne* _listener;
public:
    PaddleController(Paddle* paddle);
    ~PaddleController();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};
