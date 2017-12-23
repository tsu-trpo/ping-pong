#include "Paddle.h"
#include "DefaultMaterial.h"
#include "ObjectTags.h"
#include "VisibleRect.h"
#include "ContactHelper.h"

bool Paddle::onContact(PhysicsContact &contact)
{
    CCLOG("onContact");
    ContactHelper helper{contact, paddleTag};
    if (!helper.wasContacted()) {
        return false;
    }

    PhysicsShape *collidedShape = helper.getOther();

    if (isTagEqualTo(collidedShape, bonusTag)) {
        auto bonus = dynamic_cast<Bonus *>(collidedShape->getBody()->getNode());
        assert(bonus);
        CCLOG("WITH PADDLE");
        onContactWithBonus(bonus);
    }
    else {
        return false;
    }
    return true;
}

void Paddle::onContactWithBonus(Bonus *bonus)
{
    bonus->bonusDelete();
}

Paddle *Paddle::createWithTexture(const std::string &textureName)
{
    auto self = new Paddle();
    self->initWithFile(textureName);
    self->autorelease();
    self->_controller = std::make_shared<PaddleController>(self);

    auto bodySize = Size(self->getWidth(), self->getHeight());
    self->setPhysicsBody(PhysicsBody::createBox(bodySize, defaultMaterial));
    self->_physicsBody->setDynamic(false);
    self->_physicsBody->setName(paddleTag);
    self->_physicsBody->setContactTestBitmask(0xFFFFFFFF);

    self->_contactListener = EventListenerPhysicsContact::create();
    self->_contactListener->onContactBegin = CC_CALLBACK_1(Paddle::onContact, self);
    self->getEventDispatcher()->addEventListenerWithSceneGraphPriority(self->_contactListener, self);

    return self;
}

Rect Paddle::getRect() const
{
    return Rect(-(getContentSize().width * getScaleX() / 2.0), -(getContentSize().height * getScaleY() / 2.0),
                getContentSize().width * getScaleX(), getContentSize().height * getScaleY());
}

bool Paddle::containsTouchLocation(Touch *touch) const
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Paddle::setWidth(float newWidth)
{
    setScaleX(newWidth / getContentSize().width);
}

float Paddle::getWidth() const
{
    return getContentSize().width * getScaleX();
}

void Paddle::setHeight(float newHeight)
{
    setScaleY(newHeight / getContentSize().height);
}

float Paddle::getHeight() const
{
    return getContentSize().height * getScaleY();
}

void Paddle::setPosition(float x, float y)
{
    float rightLimit = VisibleRect::right().x - (getWidth() / 2.0);
    float leftLimit = VisibleRect::left().x + (getWidth() / 2.0);
    x = MIN(MAX(x, leftLimit), rightLimit);
    Sprite::setPosition(x, y);
}

void Paddle::setPosition(const Vec2 &position)
{
    setPosition(position.x, position.y);
}
