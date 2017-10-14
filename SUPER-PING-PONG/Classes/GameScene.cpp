#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"

USING_NS_CC;


Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}


bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    _ballStartingVelocity = Vec2(20.0f, -100.0f) * 4;
    screenSize = Director::getInstance()->getVisibleSize();

    //auto *bg = Sprite::create("pongBG.png");
    //bg->setPosition(VisibleRect::center());
    //this->addChild(bg);

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + screenSize.height * 0.1));
    this->addChild(_paddle);

    _ball = Ball::createWithTexture("res/ball.png");
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    this->addChild(_ball);

    //////////////////////////////

    schedule( CC_SCHEDULE_SELECTOR(GameScene::doStep) );

    return true;
}

void GameScene::doStep(float delta)
{
    _ball->move(delta);

    _ball->collideWithPaddle( _paddle );
}

