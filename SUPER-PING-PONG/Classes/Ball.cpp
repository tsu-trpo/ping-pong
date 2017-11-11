#include "Ball.h"

Ball* Ball::createWithTexture(std::string textureName, int minVelocity, int maxVelocity)
{
    Ball* self = new Ball();
    self->_minVelocity = minVelocity;
    self->_maxVelocity = maxVelocity;
    self->_collisionStrategy = std::make_shared<Classic>();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
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


bool Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleRect = paddle->getRect();
    paddleRect.origin.x += paddle->getPosition().x; //setting rect to it's real position
    paddleRect.origin.y += paddle->getPosition().y;

    if (getBoundingBox().intersectsRect(paddleRect))
    {
        auto ballBox = getBoundingBox();

        if( ballBox.getMaxX() > paddleRect.getMinX() && ballBox.getMinX() < paddleRect.getMaxX() &&
            ballBox.getMinY() < paddleRect.getMaxY() )
        {
            setPosition(getPosition().x, paddleRect.getMaxY() + getRadius());

            float hitDisplacement = (getPosition().x - paddle->getPosition().x) / (paddle->getContentSize().width / 2);

            _direction = Vec2(hitDisplacement, _direction.y * -1);
            _velocity = _minVelocity + (_maxVelocity - _minVelocity)* fabsf(hitDisplacement);

            CCLOG("Ball collide with Paddle at %f ", hitDisplacement);
            return true;
        }
    }
    return false;
}


bool Ball::collideWithBrick(Brick *brick)
{
    return _collisionStrategy->collideWithBrick(this, brick);
}