#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>
#include "VisibleRect.h"
#include "AudioPlayer.h"

using namespace cocos2d;


class GameScene : public cocos2d::Layer
{
    Vector <Ball*> _balls;
    Paddle* _paddle;
    Vector<Brick*> _bricks;

public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene* createScene();
    virtual bool init();

    void update(float delta);
    void move(float delta, Ball* ball);
};
