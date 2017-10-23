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