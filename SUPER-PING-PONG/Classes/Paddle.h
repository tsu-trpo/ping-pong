#pragma once
#include "PaddleController.h"
#include "cocos2d.h"
#include "BonusDropper.h"

class PaddleController;

using namespace cocos2d;

class Paddle : public Sprite {
    std::shared_ptr<PaddleController> _controller;
    EventListenerPhysicsContact *_contactListener;

public:
    static Paddle *createWithTexture(const std::string &textureName);

    Rect getRect() const;

    bool containsTouchLocation(Touch *touch) const;

    void setWidth(float newWidth);

    float getWidth() const;

    void setHeight(float newHeight);

    float getHeight() const;

    void setPosition(float x, float y);

    void setPosition(const Vec2 &position);

    bool onContact(PhysicsContact &contact);
    void onContactWithBonus(Bonus *bonus);
};
