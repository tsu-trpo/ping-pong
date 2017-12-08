#include "PaddleController.h"
#include "VisibleRect.h"

PaddleController::PaddleController(Paddle* paddle) : _paddle(paddle)
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

bool PaddleController::onTouchBegan(Touch* touch, Event* event)
{
    _rightLimit = VisibleRect::right().x - (_paddle->getWidth() / 2.0);
    _leftLimit = VisibleRect::left().x + (_paddle->getWidth() / 2.0);
    return _paddle->containsTouchLocation(touch);
}

void PaddleController::onTouchMoved(Touch* touch, Event* event)
{
    auto touchPoint = touch->getLocation();
    float x = MIN( MAX(touchPoint.x, _leftLimit), _rightLimit);
    _paddle->setPosition( Vec2(x, _paddle->getPosition().y) );
}

void PaddleController::onTouchEnded(Touch* touch, Event* event)
{
}
