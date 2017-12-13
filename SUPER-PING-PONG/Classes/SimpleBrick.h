#pragma once
#include "Brick.h"

class Brick;

class SimpleBrick : public Brick {
public:
    static Brick* createBrick(std::vector<Vector<Brick *>> &bricks);
    void onContact() override;
};