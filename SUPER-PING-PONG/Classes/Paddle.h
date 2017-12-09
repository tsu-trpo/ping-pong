#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Paddle : public Sprite {
    float _rightLimit;
    float _leftLimit;

public:
    static Paddle *createWithTexture(std::string textureName);

    virtual void onEnter() override;
    virtual void onExit() override;

    Rect getRect();
    Rect getBox();
    bool containsTouchLocation(Touch *touch);

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
};
