#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class Ball : public Sprite
{
public:
    float size = 1.0;
    static Ball* createBall();
    static Vec2 randDirection();
    float incSizeBonus();
    float decSizeBonus();
};