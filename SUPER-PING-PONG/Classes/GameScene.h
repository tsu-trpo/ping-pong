#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#pragma once

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
    Ball* _ball;
    Paddle* _paddle;
    Vector<Brick*> _bricks;

    Vec2 _ballStartingVelocity;
    Size _screenSize;

public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();

    void doStep(float delta);
};
