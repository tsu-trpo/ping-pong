#include <iostream>
#include "Ball.h"
Ball * Ball::createBall() {
    Ball *self = NULL;
    self = new Ball();
    self->initWithFile("ball.png");
    return self;
}

Vec2 Ball::randDirection()
{
    int startLeft = 0;
    float randStart = CCRANDOM_0_1();
    if (randStart < 0.5) {
        startLeft = 1;
    }

    float randStartPercentage = CCRANDOM_0_1() * 90 - 45;
    float startAngleInDegrees = startLeft * 180 + randStartPercentage;

    float xDirectionPos = cosf(CC_DEGREES_TO_RADIANS(startAngleInDegrees));
    float yDirectionPos = sinf(CC_DEGREES_TO_RADIANS(startAngleInDegrees));
    return Vec2(xDirectionPos, yDirectionPos);
}

float Ball::incSizeBonus()
{
    if (size < 5) {
        size += 0.5;
        std::cout << "current ball size: " << size << std::endl;
    }
    else {
        std::cout << "max size is reached" << std::endl;
    }
    return size;
}

float Ball::decSizeBonus()
{
    if (size > 0.3) {
        size -= 0.2;
        std::cout << "current ball size: " << size << std::endl;
    }
    else {
        std::cout << "min size is reached" << std::endl;
    }
    return size;
}

bool Ball::collide(Brick *it, Ball *ball) {
    if ((ball->getBoundingBox().intersectsRect(it->getBoundingBox()))){
        return true;
    }
    return false;
}

Vec2 Ball::newDirection(Brick *it, Ball *ball, Vec2 ballDirection) {
    auto BrickRect = it->brickRect();
    BrickRect.origin.x += it->getPositionX();
    BrickRect.origin.y += it->getPositionY();

    auto _ball = ball->getBoundingBox();
    if ((_ball.getMinY() < BrickRect.getMaxY() && _ball.getMinY() > BrickRect.getMinY()) ||
        (_ball.getMaxY() > BrickRect.getMinY() && _ball.getMaxY() < BrickRect.getMaxY()))
        {
        if (_ball.getMinX() < BrickRect.getMaxX() && _ball.getMaxX() > BrickRect.getMaxX())
        {
            ballDirection.x = fabsf(ballDirection.x);
        }
        else if (_ball.getMaxX() > BrickRect.getMinX() && _ball.getMinX() < BrickRect.getMinX())
        {
            ballDirection.x = -fabsf(ballDirection.x);
        }
        if (_ball.getMinY() < BrickRect.getMaxY() && _ball.getMinY() > BrickRect.getMinY())
        {
            ballDirection.y = fabsf(ballDirection.y);
        }
        else
        {
            ballDirection.y = -fabsf(ballDirection.y);
        }
    }
    return Vec2(ballDirection.x, ballDirection.y);
}

void Ball::changeColour(Ball *ball)
{
    ball->setColor(Color3B (random(0,255), random(0,255), random(0,255)));
}
