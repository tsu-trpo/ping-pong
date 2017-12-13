#include "BrickFactory.h"

Brick* BrickFactory::createBrick(int type) {
    if(type == 0) {
        return SimpleBrick::createBrick();
    }
}

