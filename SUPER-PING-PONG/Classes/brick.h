#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Brick : public Sprite {
private:
public:
    static Brick* createWithTexture(std::string textureName);
};


