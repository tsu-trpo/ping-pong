#pragma once
#include "Brick.h"
#include "Paddle.h"
#include "cocos2d.h"

using namespace cocos2d;

class CollisionStrategy;

class Ball : public Sprite {
    Vec2 _startPosition;
    Vec2 _startVelocity;
    float _maxSpeed;
    float _minSpeed;
    EventListenerPhysicsContact *_contactListener;

public:
    static Ball *createWithTexture(const std::string &textureName, Vec2 startPosition, Vec2 startVelocity);
    ~Ball();

    void respawn();

    void setStartPosition(Vec2 newStartPosition);
    Vec2 getStartPosition() const;

    void setStartVelocity(Vec2 newStartVelocity);
    Vec2 getStartVelocity() const;

    void setMaxSpeed(float maxSpeed);
    float getMaxSpeed() const;

    void setMinSpeed(float minSpeed);
    float getMinSpeed() const;

    void setRadius(float newRadius);
    float getRadius();

    bool onContact(PhysicsContact &contact);

    void onContactWithPaddle(Paddle *paddle);
    void onContactWithBrick(Brick *brick);
    void onContactWithBottom();
};
