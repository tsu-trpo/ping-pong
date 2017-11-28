#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
    Vector <Ball*> _balls;
    Paddle* _paddle;
    std::vector<std::vector<Brick*>> _bricks;

public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();

    void createBricks(int perLine, int perColumn);
    void update(float delta);
    void move(float delta, Ball* ball);
};
