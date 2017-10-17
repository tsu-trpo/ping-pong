#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "VisibleRect.h"
//#include <stdio.h>


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
    else if (getPosition().y < VisibleRect::bottom().y)
    {
        CCLOG("///////////////////////////////////////////////////////////////////////");
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

    if (isWidthCorrect && isHighCorrect) //is Collide with paddle
    {
        //CCLOG("Ball collide with Paddle");
        CCLOG("///////////////////////////////////////////////////////////////////////");
        setPosition(getPosition().x, highY + radius());

        float angleOffset = (float)M_PI / 2;
        float hitAngle = (paddle->getPosition() - getPosition() ).getAngle() + angleOffset;
        float velocityAngle = -_velocity.getAngle() + 0.5f * hitAngle;  // 0.5f

        float scalarVelocity = MIN(_velocity.getLength() * 1.05f, VisibleRect::top().y);    // speed

        _velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
    }
}

//bool Ball::collideWithBrick(Brick *brick)
//{
//    if( brick->getBoundingBox().intersectsRect(getBoundingBox()) )
//    {
//        _velocity *= -1;
//        return true;
//    }
//    return false;
//}

bool Ball::collideWithBrick(Brick *brick)
{
    auto brickRect = brick->getRect();
    brickRect.origin.x += brick->getPosition().x;
    brickRect.origin.y += brick->getPosition().y;

    float lowY = brickRect.getMinY();
    float midY = brickRect.getMidY();
    float highY = brickRect.getMaxY();

    float leftX = brickRect.getMinX();
    float midX = brickRect.getMidX();
    float rightX = brickRect.getMaxX();

    if (getPosition().x > leftX && getPosition().x < rightX)
    {
        if (getPosition().y > midY && getPosition().y < highY + radius())
        {
            CCLOG("Ball collide with Brick on the top");
            setPosition(getPosition().x, highY + radius());
            _velocity.y *= -1;
            return true;
        }
        else if (getPosition().y < midY && getPosition().y > lowY - radius())
        {
            CCLOG("Ball collide with Brick on the bottom");
            setPosition(getPosition().x, lowY - radius());
            _velocity.y *= -1;
            return true;
        }
    }
    else if(getPosition().y > lowY && getPosition().y < highY)
    {
        if (getPosition().x > midX && getPosition().x < rightX + radius())
        {
            CCLOG("Ball collide with Brick on the right");
            setPosition(rightX + radius(), getPosition().y);
            _velocity.x *= -1;
            return true;
        }
        else if (getPosition().y < midX && getPosition().y > leftX - radius())
        {
            CCLOG("Ball collide with Brick on the left");
            setPosition(leftX - radius(), getPosition().y);
            _velocity.x *= -1;
            return true;
        }
    }
    return false;
}