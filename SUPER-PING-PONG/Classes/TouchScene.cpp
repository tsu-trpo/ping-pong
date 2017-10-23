#include "TouchScene.h"
#include "VisibleRect.h"

USING_NS_CC;

Scene* TouchScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TouchScene::create();
    scene->addChild(layer);

   return scene;
}

bool TouchScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
   auto touchListener = EventListenerTouchOneByOne::create();

   touchListener->onTouchBegan = CC_CALLBACK_2(TouchScene::onTouchBegan, this);
   touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchEnded, this);
   touchListener->onTouchMoved = CC_CALLBACK_2(TouchScene::onTouchMoved, this);
   touchListener->onTouchCancelled = CC_CALLBACK_2(TouchScene::onTouchCancelled, this);

   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
   auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();

   auto sprite = Sprite::create("background.jpg");
   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
   this->addChild(sprite, 0);

   auto ball = Sprite::create("ball.png");
   ball->setPosition( VisibleRect::center() );
   this->addChild(ball);

   auto paddle1 = Sprite::create("paddle.png");
   paddle1->setPosition(VisibleRect::bottom());
   this->addChild(paddle1);

   return true;
}

bool TouchScene::onTouchBegan(Touch* touch, Event* event)
{
    //Vec2 touchLocation = touch->getLocation();
    //paddle1->setPosition(Vec2(touchLocation.x, paddle1->getPosition().y));
    return true;
}

void TouchScene::onTouchEnded(Touch* touch, Event* event)
{
   cocos2d::log("touch ended");
}

void TouchScene::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 touchLocation = touch->getLocation();
    paddle1->setPosition(Vec2(touchLocation.x, paddle1->getPosition().y));
    cocos2d::log("touch moved");
}

void TouchScene::onTouchCancelled(Touch* touch, Event* event)
{
   cocos2d::log("touch cancelled");
}
