#include "paddle.h"

Paddle* Paddle::createWithTexture(std::string textureName) {
    Paddle* self = new (std::nothrow) Paddle();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

