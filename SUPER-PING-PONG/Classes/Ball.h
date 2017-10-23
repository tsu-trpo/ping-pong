#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class Paddle;
class Brick;

class Ball : public Sprite
{
    Vec2 _direction;
    int _velocity;
    int _minVelocity;
    int _maxVelocity;

public:
    static Ball* createWithTexture(std::string textureName);

    float radius();

    void setDirection(Vec2 direction);
    Vec2 getDirection();

    void setVelocity(int velocity);
    int getVelocity();

    void setMinVelocity(int velocity);
    int getMinVelocity();

    void setMaxVelocity(int velocity);
    int getMaxVelocity();

    void move(float delta);
    bool collideWithBottom();
    bool collideWithPaddle(Paddle* paddle);
    bool collideWithBrick(Brick* brick);
};
