#pragma once
#include "cocos2d.h"
#include "CollisionStrategy.h"


using namespace cocos2d;

class CollisionStrategy;

class Ball : public Sprite
{
    Vec2 _startPosition;
    Vec2 _startVelocity;
    std::shared_ptr<CollisionStrategy> _collisionStrategy;

public:
    static Ball* createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startVelocity);

    void respawn();
    void setCollisionStrategy(std::shared_ptr<CollisionStrategy> newStrategy);

    void setStartPosition(Vec2 newStartPosition);
    Vec2 getStartPosition();

    void setStartVelocity(Vec2 newStartVelocity);
    Vec2 getStartVelocity();

    void setRadius(float newRadius);
    float getRadius();
};
