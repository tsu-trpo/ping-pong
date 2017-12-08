#include "Paddle.h"
#include "DefaultMaterial.h"

Paddle * Paddle::createWithTexture(const std::string &textureName)
{
    auto self = new Paddle();
    self->initWithFile(textureName);
    self->autorelease();
    self->_controller = new PaddleController(self);

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);

    return self;
}

Rect Paddle::getRect() const
{
    return Rect(
            -(getContentSize().width * getScaleX() / 2),
            -(getContentSize().height * getScaleY() / 2),
            getContentSize().width * getScaleX(),
            getContentSize().height * getScaleY());
}

bool Paddle::containsTouchLocation(Touch* touch) const
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Paddle::setWidth(float newWidth)
{
    setScaleX(newWidth  / getContentSize().width);
}

float Paddle::getWidth() const
{
    return getContentSize().width * getScaleX();
}

void Paddle::setHeight(float newHeight)
{
    setScaleY(newHeight / getContentSize().height);
}

float Paddle::getHeight() const
{
    return getContentSize().height * getScaleY();
}
