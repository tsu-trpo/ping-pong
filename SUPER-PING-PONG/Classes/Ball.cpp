#include "Ball.h"
#include "Paddle.h"
#include "VisibleRect.h"
#include <stdio.h>


Ball* Ball::createWithTexture(std::string textureName)
{

    Ball* self = new (std::nothrow) Ball();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}


float Ball::radius()
{
    return getTexture()->getContentSize().width / 2;
}


void Ball::setVelocity(Vec2 velocity)
{
    _velocity = velocity;
}


Vec2 Ball::getVelocity()
{
    return _velocity;
}


void Ball::move(float delta)
{
    this->setPosition(getPosition() + _velocity * delta);

    if (getPosition().x > VisibleRect::right().x - radius())
    {
        setPosition(VisibleRect::right().x - radius(), getPosition().y);
        _velocity.x *= -1;
    }
    else if (getPosition().x < VisibleRect::left().x + radius())
    {
        setPosition(VisibleRect::left().x + radius(), getPosition().y);
        _velocity.x *= -1;
    }
    else if (getPosition().y > VisibleRect::top().y - radius())
    {
        setPosition(getPosition().x, VisibleRect::top().y - radius());
        _velocity.y *= -1;
    }
}


void Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleRect = paddle->getRect();
    paddleRect.origin.x += paddle->getPosition().x;
    paddleRect.origin.y += paddle->getPosition().y;

    float leftX  = paddleRect.getMinX();
    float rightX = paddleRect.getMaxX();

    float midY  = paddleRect.getMidY();
    float highY = paddleRect.getMaxY();

    bool isWidthCorrect = getPosition().x > leftX && getPosition().x < rightX;
    bool isHighCorrect = getPosition().y > midY && getPosition().y <= highY + radius();

    if (isWidthCorrect && isHighCorrect)
    {
        setPosition(getPosition().x, highY + radius());

        float angleOffset = (float)M_PI / 2;
        float hitAngle = (paddle->getPosition() - getPosition() ).getAngle() + angleOffset;

        float scalarVelocity = _velocity.getLength() * 1.05f;
        float velocityAngle = -_velocity.getAngle() + 0.5f * hitAngle;

        _velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
    }
}