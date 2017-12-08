#pragma once
#include "Ball.h"
#include "Brick.h"
#include "cocos2d.h"

class Ball;
class Brick;

class CollisionStrategy {
public:
    virtual bool collideWithBrick(Ball &ball, Brick &brick)
    {
        return 0;
    };
};

class Classic : public CollisionStrategy {
    bool collideWithBrick(Ball &ball, Brick &brick) override;
};

class Sharp : public CollisionStrategy {
    bool collideWithBrick(Ball &ball, Brick &brick) override;
};

// TODO:  class Fury
