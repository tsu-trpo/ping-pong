#pragma once
#include "Brick.h"
#include "GameScene.h"
#include "ExplosionBrick.h"
#include "SimpleBrick.h"
#include "UnbreackableBrick.h"

class GameScene;

class BricksWall {
    // Vector is safer, but can works only with cocos objects
    std::vector<Vector<Brick *>> _bricks;
    int unbreackableBricksN = 0;
    int BricksCount = 0;

public:
    void createBricks(int lines, int columns, GameScene *Scene);
    static Brick *BrickFactory(int type, std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn);
};
