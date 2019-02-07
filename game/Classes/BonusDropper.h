#pragma once
#include "Brick.h"
#include "Paddle.h"
#include "cocos2d.h"

using namespace cocos2d;

class Bonus : public Sprite {
    EventListenerPhysicsContact *_contactListener;

public:
    static Bonus *createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity);
    static Bonus *dropBonus(Vec2 startPosition);

    float getRadius();

    bool onContact(PhysicsContact &contact);
    void onContactWithPaddle(Paddle *paddle);

    void bonusDelete();
};
