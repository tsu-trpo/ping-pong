#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "Brick.h"

using namespace cocos2d;
class Ball : public Sprite
{
public:
    float size = 1.0;
    static Ball* createBall();
    static Vec2 randDirection();
    bool collide(Brick *it, Ball *ball);
    float incSizeBonus();
    float decSizeBonus();
};