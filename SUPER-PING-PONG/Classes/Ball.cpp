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
    this->setPosition(getPosition() + _direction * _velocity * delta);

    if (getPosition().x > VisibleRect::right().x - radius())
    {
        setPosition(VisibleRect::right().x - radius(), getPosition().y);
        _direction.x *= -1;
    }
    else if (getPosition().x < VisibleRect::left().x + radius())
    {
        setPosition(VisibleRect::left().x + radius(), getPosition().y);
        _direction.x *= -1;
    }
    else if (getPosition().y > VisibleRect::top().y - radius())
    {
        setPosition(getPosition().x, VisibleRect::top().y - radius());
        _direction.y *= -1;
    }
}

bool Ball::collideWithBottom()
{
    return getPosition().y < VisibleRect::bottom().y;
}

void Ball::collideWithPaddle(Paddle* paddle)
{
    auto paddleRect = paddle->getRect();
    paddleRect.origin.x += paddle->getPosition().x;
    paddleRect.origin.y += paddle->getPosition().y;

    if (getBoundingBox().intersectsRect(paddleRect))
    {
        auto ball = getBoundingBox();

        if( ball.getMaxX() > paddleRect.getMinX() && ball.getMidX() < paddleRect.getMaxX() &&
                    ball.getMinY() < paddleRect.getMaxY() + radius() )
        {
            setPosition(getPosition().x, paddleRect.getMaxY() + radius());

            float hitDisplacement = (getPosition().x - paddle->getPosition().x) / (paddle->getContentSize().width / 2);
            _direction = Vec2(hitDisplacement, _direction.y * -1);

            int minVelocity = 350; // Костыль
            _velocity = MAX(minVelocity, abs(VisibleRect::top().y * hitDisplacement) - 100);

            CCLOG("Ball collide with Paddle at %f ", hitDisplacement);
        }
    }
}


bool Ball::collideWithBrick(Brick *brick)
{
    auto brickRect = brick->getRect();
    brickRect.origin.x += brick->getPosition().x;
    brickRect.origin.y += brick->getPosition().y;

    if (getBoundingBox().intersectsRect(brickRect))
    {
        auto ball = getBoundingBox();

        if ((ball.getMinY() < brickRect.getMaxY() && ball.getMinY() > brickRect.getMinY()) ||
                (ball.getMaxY() > brickRect.getMinY() && ball.getMaxY() < brickRect.getMaxY()))
        {
            if (ball.getMinX() < brickRect.getMaxX() && ball.getMaxX() > brickRect.getMaxX())
            {
                _direction.x = fabsf(_direction.x);
            } else if (ball.getMaxX() > brickRect.getMinX() && ball.getMinX() < brickRect.getMinX())
            {
                _direction.x = -fabsf(_direction.x);
            }

            if (ball.getMinY() < brickRect.getMaxY() && ball.getMinY() > brickRect.getMinY())
            {
                _direction.y = fabsf(_direction.y);
            } else
            {
                _direction.y = -fabsf(_direction.y);
            }
        }
        return true;
    }
    return false;
}
