#include "SimpleBrick.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"

Brick* SimpleBrick::createBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn) {

    SimpleBrick *self;
    self = new SimpleBrick();
    self->initWithFile("res/brick.png");
    self->autorelease();
    self->_bricks = bricks;
    self->_line = newLine;
    self->_column = newColumn;

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);
    self->_physicsBody->setName(brickTag);
    self->_physicsBody->setContactTestBitmask(0xffffffff);
    return self;
}

void SimpleBrick::onContact() {

    removeFromParent();
}
