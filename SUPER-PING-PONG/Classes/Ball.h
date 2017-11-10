#pragma once
#include "cocos2d.h"
#include "VisibleRect.h"
#include "CollisionStrategy.h"
#include "Paddle.h"
#include "Brick.h"


using namespace cocos2d;

class CollisionStrategy;

class Ball : public Sprite
{
    Vec2 _direction;
    int _velocity;

    int _minVelocity;
    int _maxVelocity;
    std::shared_ptr<CollisionStrategy> _collisionStrategy;

public:
    static Ball* createWithTexture(std::string textureName, int minVelocity, int maxVelocity);
    void setCollisionStrategy(std::shared_ptr<CollisionStrategy> strategy);

    void move(float delta);
    bool collideWithBottom();
    bool collideWithPaddle(Paddle* paddle);
    bool collideWithBrick(Brick* brick);


    double getRadius();

    void setDirection(Vec2 direction);
    Vec2 getDirection();

    void setVelocity(int velocity);
    int getVelocity();

};
