#pragma once
#include "cocos2d.h"
#include "Brick.h"

using namespace cocos2d;

class Bonus : public Sprite
{
//    Vec2 _spawnVelocity;
public:
    static Bonus* createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity);
    float getRadius();
    static Bonus* dropBonus(Brick *brick);
};
