#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Bonus : public Sprite
{
    Vec2 _spawnPosition;
    Vec2 _spawnVelocity;
public:
    static Bonus* createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity);
    float getBonusRadius();
};
