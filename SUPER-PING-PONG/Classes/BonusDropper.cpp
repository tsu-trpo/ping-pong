#include "BonusDropper.h"
#include "ContactHelper.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"
#include "VisibleRect.h"
#include "FilenameConstants.h"

bool Bonus::onContact(PhysicsContact &contact)
{
    CCLOG("onContact");
    ContactHelper helper{contact, bonusTag};
    if (!helper.wasContacted()) {
        return false;
    }

    auto bonus = dynamic_cast<Bonus *>(helper.getMain()->getBody()->getNode());
    PhysicsShape *collidedShape = helper.getOther();

    if (isTagEqualTo(collidedShape, paddleTag)) {
        auto paddle = dynamic_cast<Paddle *>(collidedShape->getBody()->getNode());
        assert(paddle);
        bonus->onContactWithPaddle(paddle);
    } else {
        return false;
    }
    return true;
}

void Bonus::onContactWithPaddle(Paddle *paddle)
{
    CCLOG("WITH PADDLE");
    bonusDelete();
}

Bonus *Bonus::createWithTexture(const std::string &textureName, Vec2 spawnPosition, Vec2 spawnVelocity)
{
    auto self = new Bonus();

    self->initWithFile(textureName);
    self->setScale(0.4, 0.4);
    self->autorelease();

    self->setPhysicsBody(PhysicsBody::createCircle(self->getRadius(), bonusMaterial));
    self->_physicsBody->setVelocity(spawnVelocity);
    self->_physicsBody->setName(bonusTag);
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);
    self->_physicsBody->setCollisionBitmask(0);

    self->setColor(Color3B(random(0, 255), random(0, 255), random(0, 255)));
    self->setPosition(spawnPosition);

    //    if(!self->_contactListener) {
    self->_contactListener = EventListenerPhysicsContact::create();
    self->_contactListener->onContactBegin = CC_CALLBACK_1(Bonus::onContact, self);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(self->_contactListener, self);
    //    }
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

Bonus *Bonus::getBonus()
{
    return this;
}

void Bonus::bonusDelete()
{
    if (this != 0) {
        removeFromParent();
        Director::getInstance()->getEventDispatcher()->removeEventListener(_contactListener);
    }
}