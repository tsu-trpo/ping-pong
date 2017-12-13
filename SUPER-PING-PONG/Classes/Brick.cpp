#include "Brick.h"
#include "DefaultMaterial.h"

Rect Brick::getRect()
{
    return Rect(-(getContentSize().width * getScaleX() * 0.5), -(getContentSize().height * getScaleY() * 0.5),
                getContentSize().width * getScaleX(), getContentSize().height * getScaleY());
}

Rect Brick::getBox()
{
    // setting rect to it's real position
    auto box = getRect();
    box.origin.x += getPosition().x;
    box.origin.y += getPosition().y;
    return box;
}

float Brick::getWidth()
{
    return getContentSize().width * getScaleX();
}

void Brick::setWidth(float newWidth)
{
    setScaleX(newWidth / getContentSize().width);
}

float Brick::getHeight()
{
    return getContentSize().height * getScaleY();
}

void Brick::setHeight(float newHeight)
{
    setScaleY(newHeight / getContentSize().height);
}
