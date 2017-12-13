#include "ExplosionBrick.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"

Brick* ExplosionBrick::createBrick(std::vector<Vector<Brick*>> &bricks) {

    ExplosionBrick *self;
    self = new ExplosionBrick();
    self->initWithFile("res/brickRed.png");
    self->autorelease();
    self->_bricks = bricks;

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);
    self->_physicsBody->setName(brickTag);
    self->_physicsBody->setContactTestBitmask(0xffffffff);
    return self;
}

void ExplosionBrick::onContact() {
    removeFromParent();
}
