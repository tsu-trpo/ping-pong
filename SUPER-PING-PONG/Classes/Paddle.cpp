#include "Paddle.h"
#include "VisibleRect.h"

Paddle *Paddle::createWithTexture(std::string textureName)
{
    Paddle *self = new (std::nothrow) Paddle();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

void Paddle::onEnter()
{
    Sprite::onEnter();

    _rightLimit = VisibleRect::right().x - getContentSize().width * getScaleX() * 0.5;
    _leftLimit = VisibleRect::left().x + getContentSize().width * getScaleX() * 0.5;

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Paddle::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Paddle::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Paddle::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Paddle::onExit()
{
    Sprite::onExit();
}

Rect Paddle::getRect()
{
    return Rect(-(getContentSize().width * getScaleX() * 0.5), -(getContentSize().height * getScaleY() * 0.5),
                getContentSize().width * getScaleX(), getContentSize().height * getScaleY());
}

Rect Paddle::getBox()
{
    auto box = getRect();
    box.origin.x += getPosition().x;  // setting rect to it's real position
    box.origin.y += getPosition().y;
    return box;
}

bool Paddle::containsTouchLocation(Touch *touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Paddle::onTouchBegan(Touch *touch, Event *event)
{
    return containsTouchLocation(touch);
}

void Paddle::onTouchMoved(Touch *touch, Event *event)
{
    auto touchPoint = touch->getLocation();
    float x = MIN(MAX(touchPoint.x, _leftLimit), _rightLimit);
    setPosition(Vec2(x, getPosition().y));
}

void Paddle::onTouchEnded(Touch *touch, Event *event) {}
