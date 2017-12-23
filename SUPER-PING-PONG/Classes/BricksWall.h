#pragma once
#include "Brick.h"
#include "BrickFactory.h"
#include "GameScene.h"

class GameScene;

class BricksWall {
    // Vector is safer, but can works only with cocos objects
    std::vector<Vector<Brick *>> _bricks;

public:
    void createBricks(int perLine, int perColumn, GameScene *Scene);
};
