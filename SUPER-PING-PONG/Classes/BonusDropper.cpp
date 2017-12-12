#include "BonusDropper.h"
#include "DefaultMaterial.h"

Bonus* Bonus::createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity)
{
    auto self = new Bonus();
    self->_spawnPosition = spawnPosition;
    self->_spawnVelocity = spawnVelocity;
    self->_position = spawnPosition;

    self->initWithFile(textureName);
    self->setScale(0.4, 0.4);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getBonusRadius(), bonusMaterial));
    self->_physicsBody->setVelocity(spawnVelocity);
    self->_physicsBody->setName("bonus");
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);


    self->setColor(Color3B (random(0,255), random(0,255), random(0,255)));
    return self;
}

float Bonus::getBonusRadius()
{
    return getContentSize().width * getScaleX() * 0.85;
}

void Bonus::setBonusPosition(Node *brick, Bonus *bonus)
{
    bonus->setPosition(brick->getPosition());
}
