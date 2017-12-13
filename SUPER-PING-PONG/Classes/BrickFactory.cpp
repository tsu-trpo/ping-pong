#include "BrickFactory.h"

Brick* BrickFactory::createBrick(int type, std::vector<Vector<Brick *>> &bricks) {
    if(type == 0) {
        return SimpleBrick::createBrick(bricks);
    }

    if(type == 1) {
        return ExplosionBrick::createBrick(bricks);
    }
}

