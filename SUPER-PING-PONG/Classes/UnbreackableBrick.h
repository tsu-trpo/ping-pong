#include "Brick.h"

class UnbreackableBrick : public Brick {
public:
    static Brick *createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn);
    bool onContact() override;
};
