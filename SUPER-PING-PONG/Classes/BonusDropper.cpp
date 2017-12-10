#include "BonusDropper.h"
#include "DefaultMaterial.h"

Bonus* Bonus::createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity)
{
    auto self = new Bonus();
    self->_spawnPosition = spawnPosition;
    self->_spawnVelocity = spawnVelocity;
    self->setColor(Color3B (random(0,255), random(0,255), random(0,255)));
    self->setScale(0.4, 0.4);
    self->_position = spawnPosition;

    self->initWithFile(textureName);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getBonusRadius(), defaultMaterial));
    self->_physicsBody->setVelocity(spawnVelocity);

    return self;
}

float Bonus::getBonusRadius()
{
    return getContentSize().width * getScaleX() / 2;
}