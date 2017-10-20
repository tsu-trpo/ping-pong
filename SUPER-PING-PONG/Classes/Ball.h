#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class Paddle;
class Brick;

class Ball : public Sprite
{
    Vec2 _direction;
    float _velocity;

public:
    static Ball* createWithTexture(std::string textureName);

    float radius();

    void setDirection(Vec2 direction);
    Vec2 getDirection();

    void setVelocity(int velocity);
    int getVelocity();

    void move(float delta);
    bool collideWithBottom();
    void collideWithPaddle(Paddle* paddle);
    bool collideWithBrick(Brick* brick);
};
