#pragma once
#include "Brick.h"
#include "cocos2d.h"

using namespace cocos2d;

class Bonus : public Sprite {
public:
    void pushBonus(Bonus *bonus);
    static Bonus *createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity);
    float getRadius();
    static Bonus *dropBonus(Vec2 bonusStartPosition);
};
