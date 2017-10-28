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

    unsigned int perLine = 7;
    unsigned int perColumn = 2;
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;
    bricks_m = Vector<Brick*>(perLine*perColumn);
    for(unsigned int i = 0; i < (perLine*perColumn); i++) {
        Brick* br = Brick::createWithTexture("brick.jpg");
        br->setScaleY(0.3);
        br->setScaleX(0.3);
        br->setColor(Color3B(random(0,255),random(0,255),random(0,255)));
        this->addChild(br);
        bricks_m.pushBack(br);
    }

    float width_of_brick = bricks_m.at(0)->getContentSize().width * bricks_m.at(0)->getScaleX();
    float height_of_brick = bricks_m.at(0)->getContentSize().height * bricks_m.at(0)->getScaleY();
    unsigned int oneside = perLine/2;

    int flag = perLine%2; //если четное

    float x = center - width_of_brick*oneside - (width_of_brick*flag)/2 + width_of_brick/2;
    float y = top - height_of_brick/2;

    int k = 0;
    for(int j = 0; j < perColumn; j++) {
        for (int i = 0; i < perLine; i++) {
            log("add");
            bricks_m.at(k)->setPosition(x, y);
            x += width_of_brick;
            k++;
        }
        y -= height_of_brick;
        x = center - width_of_brick*oneside - (width_of_brick*flag)/2 + width_of_brick/2;
    }

    paddle1 = Paddle::createWithTexture("pad.png");
    paddle1->setPosition(VisibleRect::bottom());
    this->addChild(paddle1);

    glob = Ball::createWithTexture("ball.png");
    glob->setPosition(VisibleRect::center());
    glob->setVelocity(3);
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

    for(auto i = 0; i < bricks_m.size(); i++) {
        if(glob->collideWithBrick(bricks_m.at(i))) {
            removeChild(bricks_m.at(i));
            bricks_m.erase(i);
            cocos2d::log("sdafasdfasdf");
        };
    }


}
