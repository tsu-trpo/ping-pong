#pragma once
#include "Brick.h"
#include "Paddle.h"
#include "cocos2d.h"

using namespace cocos2d;

class Bonus : public Sprite {
    EventListenerPhysicsContact *_contactListener;

public:
    //    ~Bonus(){};
    void pushBonus(Bonus *bonus);
    static Bonus *createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity);
    float getRadius();

    static Bonus *dropBonus(Vec2 bonusStartPosition);
    Bonus *getBonus();
    void bonusDelete();

    bool onContact(PhysicsContact &contact);
    void onContactWithPaddle(Paddle *paddle);
};
