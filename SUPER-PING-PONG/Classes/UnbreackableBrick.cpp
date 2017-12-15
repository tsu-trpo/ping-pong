#include "UnbreackableBrick.h"

Brick* UnbreackableBrick::createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn) {

    UnbreackableBrick *self;
    self = new UnbreackableBrick();
    self->initWithFile("res/brickGrey.png");
    self->initBrick(bricks, newLine, newColumn);
    return self;
}

bool UnbreackableBrick::onContact() {
    return false;
}
