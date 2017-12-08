#pragma once
#include "cocos2d.h"
#include "PaddleController.h"

class PaddleController;

using namespace cocos2d;

class Paddle : public Sprite
{
    std::shared_ptr<PaddleController> _controller;
public:
    static Paddle* createWithTexture(const std::string &textureName);

    Rect getRect() const;
    bool containsTouchLocation(Touch* touch) const;

    void setWidth(float newWidth);
    float getWidth() const;

    void setHeight(float newHeight);
    float getHeight() const;
};
