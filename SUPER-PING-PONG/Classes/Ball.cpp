#include "Ball.h"
#include "DefaultMaterial.h"

Ball *Ball::createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startVelocity)
{
    auto self = new Ball();
    self->_startVelocity = startVelocity;
    self->_startPosition = startPosition;
    // TODO: Change class CollisionStrategy
    self->_collisionStrategy = std::make_shared<Classic>();
    self->_position = startPosition;

    self->initWithFile(textureName);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getRadius(), defaultMaterial));
    self->_physicsBody->setVelocity(startVelocity);

    return self;
}

void Ball::respawn()
{
    _position = _startPosition;
    _physicsBody->setVelocity(_startVelocity);
}

void Ball::setStartPosition(Vec2 newStartPosition)
{
    _startPosition = newStartPosition;
}

Vec2 Ball::getStartPosition()
{
    return _startPosition;
}

void Ball::setStartVelocity(Vec2 newStartVelocity)
{
    _startVelocity = newStartVelocity;
}

Vec2 Ball::getStartVelocity()
{
    return _startVelocity;
}

void Ball::setRadius(float newRadius)
{
    // из формулы radius == scale * width / 2
    // получаем: scale == radius * 2 / width
    setScale(newRadius * 2 / getContentSize().width);
}

float Ball::getRadius()
{
    return getContentSize().width * getScaleX() / 2;
}
