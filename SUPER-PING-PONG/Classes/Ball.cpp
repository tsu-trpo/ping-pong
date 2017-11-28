#include "Ball.h"


Ball* Ball::createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startVelocity)
{
    auto self = new Ball();
    self->_startVelocity = startVelocity;
    self->_startPosition = startPosition;
    //TODO: Change class CollisionStrategy
    self->_collisionStrategy = std::make_shared<Classic>();
    self->_position = startPosition;

    self->initWithFile(textureName);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(10,PhysicsMaterial(0.1f, 1.0f, 0.0f)));
    self->_physicsBody->setVelocity(startVelocity);
    //TODO: Change in future
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

    return self;
}


void Ball::respawn()
{
    _position = _startPosition;
    _physicsBody->setVelocity(_startVelocity);
}


void Ball::setCollisionStrategy(std::shared_ptr<CollisionStrategy> strategy)
{
    _collisionStrategy = strategy;
}


void Ball::setStartPosition(Vec2 startPosition)
{
    _startPosition = startPosition;
}


Vec2 Ball::getStartPosition()
{
    return _startPosition;
}


void Ball::setStartVelocity(Vec2 startVelocity)
{
    _startVelocity = startVelocity;
}


Vec2 Ball::getStartVelocity()
{
    return _startVelocity;
}
