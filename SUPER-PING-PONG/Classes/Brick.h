#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Brick : public Sprite {
public:
    Rect getRect();
    Rect getBox();

    float getWidth();
    void setWidth(float newWidth);

    float getHeight();
    void setHeight(float newHeight);
    virtual void onContact() = 0;
};
