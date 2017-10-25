#include "Brick.h"

Brick * Brick::createBrick() {
    Brick *self = NULL;
    self = new Brick();
    self->initWithFile("white.png");
    return self;
}

Rect Brick::brickRect() {
    return Rect(
            -(getContentSize().width * getScaleX() * 0.5),
            -(getContentSize().height * getScaleY() * 0.5),
            getContentSize().width * getScaleX(),
            getContentSize().height * getScaleY());
}