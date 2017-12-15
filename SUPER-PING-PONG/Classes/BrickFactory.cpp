#include "BrickFactory.h"
#include "TypesBricks.h"

Brick *BrickFactory::createBrick(int type, std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn)
{
    if (type == simple) {
        return SimpleBrick::createBrick(bricks, newLine, newColumn);
    }

    if (type == explosion) {
        return ExplosionBrick::createBrick(bricks, newLine, newColumn);
    }

    if (type == unbreackable) {
        return UnbreackableBrick::createBrick(bricks, newLine, newColumn);
    }
}
