#include "BonusDropper.h"
#include "DefaultMaterial.h"
#include "FilenameConstants.h"
#include "ObjectTags.h"

Bonus *Bonus::createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity)
{
    auto self = new Bonus();

    self->initWithFile(textureName);
    self->setScale(0.4, 0.4);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getRadius(), bonusMaterial));
    self->_physicsBody->setVelocity(spawnVelocity);
    self->_physicsBody->setName(tag::bonus);
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
    self->_physicsBody->setCollisionBitmask(0);

    self->setColor(Color3B(random(0, 255), random(0, 255), random(0, 255)));
    self->setPosition(spawnPosition);
    return self;
}

float Bonus::getRadius()
{
    return getContentSize().width * getScaleX() * 0.85;
}

Bonus *Bonus::dropBonus(Vec2 startPosition)
{
    Vec2 bonusStartVelocity = Vec2(0, -300);
    Bonus *bonus = Bonus::createWithTexture(file::texture::bonus, startPosition, bonusStartVelocity);
    bonus->setPosition(startPosition);
    Director::getInstance()->getRunningScene()->addChild(bonus);
    return bonus;
}
