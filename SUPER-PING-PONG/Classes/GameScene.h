#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>
#pragma once

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
    Vector <Ball*> _balls;
    Paddle* _paddle;
    Vector<Brick*> _bricks;

    Vec2 _ballStartingDirection;
    int _ballStartingVelocity;
    Size _screenSize;
//    int _life;
//    int _score;
//    int _currentLevel;
//    Label* _scoreLabel;
//    Label* _lifesLabel;

public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float delta);
    void move(float delta, Ball* ball);
};
