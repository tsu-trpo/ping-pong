#include "ExplosionBrick.h"

Brick *ExplosionBrick::createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn)
{
    ExplosionBrick *self;
    self = new ExplosionBrick();
    self->initWithFile("res/brickRed.png");
    self->initBrick(bricks, newLine, newColumn);
    return self;
}

bool ExplosionBrick::onContact()
{
    for (int i = _line - 1; i < _line + 2; i++) {
        if (i < 0|| i >= _bricks->size()) {
            continue;
        }

        for (int j = _column - 1; j < _column + 2; j++) {
            if (j == _bricks->at(i).size()) {
                break;
            }
            if (j == -1) {
                continue;
            }
            _bricks->at(i).at(j)->removeFromParent();
        }
    }
    return true;
}
