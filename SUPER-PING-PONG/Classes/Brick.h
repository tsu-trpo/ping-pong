#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Brick : public Sprite
{
public:
    static Brick* createBrick();
    Rect brickRect();
};