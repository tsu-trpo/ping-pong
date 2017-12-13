#pragma once
#include "Brick.h"

class Brick;

class SimpleBrick : public Brick {
public:
    static Brick* createBrick();
    void onContact() override;
};