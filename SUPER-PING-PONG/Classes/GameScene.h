#pragma once

#include <vector>
#include "Ball.h"
#include "Brick.h"
#include "BrickFactory.h"
#include "BricksWall.h"
#include "Paddle.h"
#include "cocos2d.h"
using namespace cocos2d;
class BricksWall;

class GameScene : public Layer {
    Vector<Ball *> _balls;
    BricksWall *_wall;
    Paddle *_paddle;

public:
    CREATE_FUNC(GameScene);
    static Scene *createScene();
    virtual bool init();
};
