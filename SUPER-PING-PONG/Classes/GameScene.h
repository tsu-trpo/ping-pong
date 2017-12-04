#pragma once

#include "cocos2d.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>

using namespace cocos2d;


class GameScene : public Layer
{
    Vector <Ball*> _balls;
    Paddle* _paddle;
    //Vector is safer, but can works only with cocos objects
    std::vector<Vector<Brick*>> _bricks;

public:
    CREATE_FUNC(GameScene);
    static Scene* createScene();
    virtual bool init();

    void createBricks(int perLine, int perColumn);
    void update(float delta);
};
