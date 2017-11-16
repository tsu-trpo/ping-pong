#include "Ball.h"

Ball* Ball::createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startDirection, int startVelocity)
{
    Ball* self = new Ball();
    self->_startPosition = startPosition;
    self->_position = startPosition;

    self->_startDirection = startDirection;
    self->_direction = startDirection;

    self->_startVelocity = startVelocity;
    self->_velocity = startVelocity;

    // default values
    self->_minVelocity = 550;
    self->_maxVelocity = VisibleRect::top().y;
    self->_collisionStrategy = std::make_shared<Classic>();

    self->initWithFile(textureName);
    self->autorelease();

    return self;
}


void Ball::move(float delta)
{
    setPosition(getPosition() + _direction * _velocity * delta);

    if (getPosition().x > VisibleRect::right().x - getRadius())
    {
        setPosition(VisibleRect::right().x - getRadius(), getPosition().y);
        _direction.x *= -1;
    }
    else if (getPosition().x < VisibleRect::left().x + getRadius())
    {
        setPosition(VisibleRect::left().x + getRadius(), getPosition().y);
        _direction.x *= -1;
    }
    if (getPosition().y > VisibleRect::top().y - getRadius())
    {
        setPosition(getPosition().x, VisibleRect::top().y - getRadius());
        _direction.y *= -1;
    }
}


bool Ball::collideWithBottom()
{
    return getPosition().y < VisibleRect::bottom().y;
}


void Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleBox = paddle->getBox();

    if (getBoundingBox().intersectsRect(paddleBox))
    {
        auto ballBox = getBoundingBox();

        if( ballBox.getMaxX() > paddleBox.getMinX() && ballBox.getMinX() < paddleBox.getMaxX() &&
            ballBox.getMinY() < paddleBox.getMaxY() )
        {
            setPosition(getPosition().x, paddleBox.getMaxY() + getRadius());

            float hitDisplacement = (getPosition().x - paddle->getPosition().x) / (paddle->getContentSize().width / 2);

            _direction = Vec2(hitDisplacement, _direction.y * -1);
            _velocity = _minVelocity + (_maxVelocity - _minVelocity)* fabsf(hitDisplacement);

            //Todo play HitEffect
            CCLOG("Ball collide with Paddle at %f ", hitDisplacement);
        }
    }
}


bool Ball::collideWithBrick(Brick *brick)
{
    return _collisionStrategy->collideWithBrick(this, brick);
}


void Ball::respawn()
{
    _position = _startPosition;
    _direction = _startDirection;
    _velocity = _startVelocity;
}



void Ball::setCollisionStrategy(std::shared_ptr<CollisionStrategy> strategy)
{
    _collisionStrategy = strategy;
}
double Ball::getRadius()
{
    return getContentSize().width * getScaleX() * 0.5;
}


void Ball::setDirection(Vec2 direction)
{
    _direction = direction;
}
Vec2 Ball::getDirection()
{
    return _direction;
}


void Ball::setVelocity(int velocity)
{
    _velocity = velocity;
}
int Ball::getVelocity()
{
    return _velocity;
}


void Ball::setStartPosition(Vec2 startPosition)
{
    _startPosition = startPosition;
}
Vec2 Ball::getStartPosition()
{
    return _startPosition;
}


void Ball::setStartDirection(Vec2 startDirection)
{
    _startDirection = startDirection;
}
Vec2 Ball::getStartDirection()
{
    return _startDirection;
}


void Ball::setStartVelocity(int startVelocity)
{
    _startVelocity = startVelocity;
}
int Ball::getStartVelocity()
{
    return _startVelocity;
}


void Ball::setMinVelocity(int minVelocity)
{
    _minVelocity = minVelocity;
}
int Ball::getMinVelocity()
{
    return _minVelocity;
}


void Ball::setMaxVelocity(int maxVelocity)
{
    _maxVelocity = maxVelocity;
}
int Ball::getMaxVelocity()
{
    return _maxVelocity;
}

