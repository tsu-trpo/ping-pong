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

    _screenSize = Director::getInstance()->getVisibleSize();
    _ballStartingDirection = Vec2(0, -1);
    _ballStartingVelocity = 300;
    int ballMinVelocity = 550;
    int ballMaxVelocity = VisibleRect::top().y;

    /// Background ///

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bg_1.ogg", true);
    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    this->addChild(bg);


    /// Paddle ///

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + _screenSize.height * 0.07));
    _paddle->setScaleX(1.2);

    this->addChild(_paddle);

    /// Balls ///

    for(int i = 0; i < 3; i++)
    {
        _balls.pushBack(Ball::createWithTexture("res/ball.png", ballMinVelocity, ballMaxVelocity));
        _balls.at(i)->setPosition( VisibleRect::center().x +i , VisibleRect::center().y +i);
        _balls.at(i)->setVelocity( _ballStartingVelocity );
        _balls.at(i)->setDirection( _ballStartingDirection);

        this->addChild(_balls.at(i));
    }

    /// Update method ///

    schedule( CC_SCHEDULE_SELECTOR(GameScene::update) );

    return true;
}


void GameScene::update(float delta)
{
    for(auto ball : _balls)
    {
        ball->move(delta);

        if(ball->collideWithPaddle( _paddle ))
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/jump.wav", false, 1.0f, 1.0f, 1.0f);
        }

        for( auto it = _bricks.begin(); it != _bricks.end(); it++)
        {
            if (ball->collideWithBrick(*it))
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/hit.wav", false, 1.0f, 1.0f, 1.0f);
                CCLOG("Delete Brick");

                if(_bricks.size() == 0)
                {
                    CCLOG("WINNER WINNER CHICKEN DINNER" );
                }
            }
        }

        if(ball->collideWithBottom())
        {
            CCLOG("BETTER LUCK NEXT TIME" );
        }
    }
}
