#pragma once
#include "Brick.h"
#include "SimpleBrick.h"

class Brick;
class SimpleBrick;

class BrickFactory {
public:
    static Brick *createBrick(int type);
};