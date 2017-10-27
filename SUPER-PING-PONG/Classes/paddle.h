#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Paddle : public Sprite {
private:
public:
    static Paddle* createWithTexture(std::string textureName);
};

