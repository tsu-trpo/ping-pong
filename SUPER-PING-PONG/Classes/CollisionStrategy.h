#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Brick.h"
// Needs Brick class methods: getPosition, getRect

class Ball;
class Brick;

class CollisionStrategy
{
public:
    virtual bool collideWithBrick(Ball* ball, Brick* brick){};
};


class Classic : public CollisionStrategy
{
    bool collideWithBrick(Ball* ball, Brick* brick) override;
};


class Sharp : public CollisionStrategy
{
    bool collideWithBrick(Ball* ball, Brick* brick) override;
};


//class Fury : public CollisionStrategy
//{
//public:
//    bool collideWithBrick(Ball* ball, Brick* brick) override;
//};

