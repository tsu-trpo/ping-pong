#include "BrickFactory.h"
#include "TypesBricks.h"

Brick *BrickFactory::createBrick(int type, std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn)
{
    switch (type) {
    case simple:
        return SimpleBrick::createBrick(bricks, newLine, newColumn);
    case explosion:
        return ExplosionBrick::createBrick(bricks, newLine, newColumn);
    case unbreackable:
        return UnbreackableBrick::createBrick(bricks, newLine, newColumn);
    default:;
    }
}
