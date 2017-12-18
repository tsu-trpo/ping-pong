#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Life: public Node {
    int _life = 3;
    Label *_label = nullptr;
public:
    Life();
    ~Life();
private:
    void updateLabel();
    void addListeners();

};
