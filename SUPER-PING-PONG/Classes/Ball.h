#pragma once
#include "cocos2d.h"
#include "VisibleRect.h"
#include "CollisionStrategy.h"
#include "Paddle.h"
#include "Brick.h"
#include "AudioPlayer.h"



using namespace cocos2d;

class CollisionStrategy;

class Ball : public Sprite
{
    Vec2 _direction;
    int _velocity;

    int _minVelocity;
    int _maxVelocity;
    Vec2 _startPosition;
    Vec2 _startDirection;
    int _startVelocity;

    std::shared_ptr<CollisionStrategy> _collisionStrategy;

public:
    static Ball* createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startDirection, int startVelocity);

    void move(float delta);
    bool collideWithBottom();
    void collideWithPaddle(Paddle* paddle);
    bool collideWithBrick(Brick* brick);

    void respawn();
    void setCollisionStrategy(std::shared_ptr<CollisionStrategy> strategy);
    double getRadius();

    void setDirection(Vec2 direction);
    Vec2 getDirection();

    void setVelocity(int velocity);
    int getVelocity();

    void setMinVelocity(int minVelocity);
    int getMinVelocity();

    void setMaxVelocity(int maxVelocity);
    int getMaxVelocity();

    void setStartPosition(Vec2 startPosition);
    Vec2 getStartPosition();

    void setStartDirection(Vec2 startDirection);
    Vec2 getStartDirection();

    void setStartVelocity(int startVelocity);
    int getStartVelocity();

};
