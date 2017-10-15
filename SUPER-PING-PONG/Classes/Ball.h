#ifndef Ball_h
#define Ball_h
#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class Ball : public Sprite
{
public:
    static Ball* createBall();
};
#endif /* Ball_h */