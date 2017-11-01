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
    return Rect(
            -(getContentSize().width * getScaleX() / 2),
            -(getContentSize().height * getScaleY() / 2),
            getContentSize().width * getScaleX(),
            getContentSize().height * getScaleY());
}