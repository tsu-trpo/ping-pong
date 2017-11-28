#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Brick : public Sprite
{
public:

    static Brick* createWithTexture(const std::string &textureName);
    Rect getRect();
    Rect getBox();

    float getWidth();
    float getHeight();
    void setWidth(float newWidth);
    void setHeight(float newHeight);
};
