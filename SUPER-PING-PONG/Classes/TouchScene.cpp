#include "TouchScene.h"
#include "VisibleRect.h"
#include <iostream>


USING_NS_CC;

Scene* TouchScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TouchScene::create();
    scene->addChild(layer);
    scene->setScale(0.97); //это плохо

   return scene;
}

bool TouchScene::init()
{
    if ( !Layer::init() ) {
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

    bricks_m = std::vector<Brick*>(2*2);
    for(int i = 0; i<4; i++) {
        Brick* br = Brick::createWithTexture("brick.jpg");
        br->setPosition(VisibleRect::center());
        br->setScaleY(0.3);
        br->setScaleX(0.3);
        this->addChild(br);
        bricks_m.push_back(br);
    }

    paddle1 = Paddle::createWithTexture("pad.png");
    paddle1->setPosition(VisibleRect::bottom());
    this->addChild(paddle1);

    glob = Ball::createWithTexture("ball.png");
    glob->setPosition(VisibleRect::center());
    glob->setVelocity(2);
    glob->setDirection(Vec2(1,1));
    glob->setScale(0.5);
    this->addChild(glob);
    schedule( CC_SCHEDULE_SELECTOR(TouchScene::doStep) );

   return true;
}

bool TouchScene::onTouchBegan(Touch* touch, Event* event) {
    return true;
}

void TouchScene::onTouchEnded(Touch* touch, Event* event) {
    cocos2d::log("touch ended");
}

void TouchScene::onTouchMoved(Touch* touch, Event* event) {
    auto touchLocation = touch->getLocation();
    paddle1->setPosition(Vec2(touchLocation.x, paddle1->getPosition().y));
    std::cout << paddle1->getPosition().x << std::endl;
    cocos2d::log("touch moved");
}

void TouchScene::onTouchCancelled(Touch* touch, Event* event) {
    cocos2d::log("touch cancelled");
}

void TouchScene::doStep(float delta) {
    if(glob->collideWithPaddle(paddle1)) {
        cocos2d::log("COLLIDE");
    }
    glob->move(delta);


}
