#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Brick.h"


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


// TODO:  class Fury
