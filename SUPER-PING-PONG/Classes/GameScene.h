#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#pragma once

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
    Ball* _ball;
    Paddle* _paddle;
    Vec2 _ballStartingVelocity;
    Size screenSize;

public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();

    void doStep(float delta);
};
