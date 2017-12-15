#pragma once
#include "Brick.h"
#include "ExplosionBrick.h"
#include "SimpleBrick.h"
#include "UnbreackableBrick.h"

class Brick;
class SimpleBrick;

class BrickFactory {
public:
    static Brick *createBrick(int type, std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn);
};