#include "SimpleBrick.h"
#include "DefaultMaterial.h"

Brick* SimpleBrick::createBrick() {

    SimpleBrick *self;
    self = new SimpleBrick();
    self->initWithFile("res/brick.png");
    self->autorelease();

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);

    return self;
}

void SimpleBrick::onContact() {

}
