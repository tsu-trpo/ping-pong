#include "Brick.h"


Brick* Brick::createWithTexture(std::string textureName)
{

    Brick* self = new (std::nothrow) Brick();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

Rect Brick::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}