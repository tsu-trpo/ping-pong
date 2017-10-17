#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class Paddle;
class Brick;

class Ball : public Sprite
{
    Vec2 _velocity;

public:
    static Ball* createWithTexture(std::string textureName);

    float radius();

    void setVelocity(Vec2 velocity);
    Vec2 getVelocity();

    void move(float delta);
    void collideWithPaddle(Paddle* paddle);
    bool collideWithBrick(Brick* brick);
};