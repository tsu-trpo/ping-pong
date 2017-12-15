#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Score : public Node {
    unsigned int _score = 0;
    unsigned int _multiplier = 1;
    Label *_label = nullptr;

public:
    Score();
    ~Score();


private:
    void updateLabel();
    void addListeners();
};
