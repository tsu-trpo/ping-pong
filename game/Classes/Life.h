#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Life : public Node {
    Vector<Sprite *> _bar;
    int _life = 3;
    const int _maxLives = 5;

public:
    Life();
    ~Life();

private:
    void updateLabel();
    void addListeners();
};
