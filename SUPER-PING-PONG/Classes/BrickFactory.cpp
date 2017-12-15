#include "BrickFactory.h"

Brick *BrickFactory::createBrick(int type, std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn)
{
    if (type == 0) {
        return SimpleBrick::createBrick(bricks, newLine, newColumn);
    }

    if (type == 1) {
        return ExplosionBrick::createBrick(bricks, newLine, newColumn);
    }

    if (type == 2) {
        return UnbreackableBrick::createBrick(bricks, newLine, newColumn);
    }
}
