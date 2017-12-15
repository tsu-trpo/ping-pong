#pragma once
#include "Brick.h"

class Brick;

class ExplosionBrick : public Brick {
public:
    static Brick *createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn);
    bool onContact() override;
};
