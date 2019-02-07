#include "Brick.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"

Brick *Brick::createWithTexture(const std::string &textureName)
{
    Brick *self = new Brick();
    self->initWithFile(textureName);
    self->autorelease();

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);
    self->_physicsBody->setName(tag::brick);
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

    return self;
}

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

void Brick::deleteBrick()
{
    removeFromParent();
}
