#pragma once
#include "paddle.h"
#include "cocos2d.h"
#include <iostream>

using namespace cocos2d;

class Ball : public Sprite {
    Vec2 direction_m;
    int velocity_m;
    float radius;
public:
    static Ball* createWithTexture(std::string textureName);

    void setDirection(Vec2 direction);
    Vec2 getDirection();

    void setVelocity(int velocity);

    float getRadius();

    void move(float delta);

    bool collideWithPaddle(Paddle* paddle);

};