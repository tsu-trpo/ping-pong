#include "PaddleController.h"
#include "VisibleRect.h"

PaddleController::PaddleController(Paddle *paddle)
    : _paddle(paddle)
{
    _listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(PaddleController::onTouchBegan, this);
    _listener->onTouchMoved = CC_CALLBACK_2(PaddleController::onTouchMoved, this);
    _listener->onTouchEnded = CC_CALLBACK_2(PaddleController::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, _paddle);
}

PaddleController::~PaddleController()
{
    _eventDispatcher->removeEventListener(_listener);
}

bool PaddleController::onTouchBegan(Touch *touch, Event *event)
{
    return _paddle->containsTouchLocation(touch);
}

void PaddleController::onTouchMoved(Touch *touch, Event *event)
{
    float rightLimit = _paddle->getRightLimit();
    float leftLimit = _paddle->getLeftLimit();
    auto touchPoint = touch->getLocation();
    float x = MIN(MAX(touchPoint.x, leftLimit), rightLimit);
    _paddle->setPosition(Vec2(x, _paddle->getPosition().y));
}

void PaddleController::onTouchEnded(Touch *touch, Event *event) {}
