#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class Paddle : public Sprite
{
    //float _size = 1.0;
    float _rightLimit;
    float _leftLimit;

public:
    static Paddle* createWithTexture(std::string textureName);

    virtual void onEnter() override;
    virtual void onExit() override;

    cocos2d::Rect getRect();
    bool containsTouchLocation(cocos2d::Touch* touch);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};