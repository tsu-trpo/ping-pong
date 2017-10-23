#include "Brick.h"

Brick * Brick::createBrick() {
    Brick *self = NULL;
    self = new Brick();
    self->initWithFile("brick_block.png");
    return self;
}