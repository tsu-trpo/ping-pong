#include "SimpleBrick.h"

Brick* SimpleBrick::createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn) {

    SimpleBrick *self;
    self = new SimpleBrick();
    self->initWithFile("res/brick.png");
    self->initBrick(bricks, newLine, newColumn);
    return self;
}

void SimpleBrick::onContact() {

    removeFromParent();
}
