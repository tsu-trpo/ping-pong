#include "GameScene.h"
#include "GameOverScene.h"
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

    //////////////////////////////

    _screenSize = Director::getInstance()->getVisibleSize();
    _ballStartingDirection = Vec2(0, -1);
    _ballStartingVelocity = 300;
    _lifes = 3;
    _score = 0;

    //////////////////////////////

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bg_1.ogg", true);
    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    this->addChild(bg);

    //////////////////////////////

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + _screenSize.height * 0.07));
    this->addChild(_paddle);

    //////////////////////////////

    _ball = Ball::createWithTexture("res/ball.png");
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    _ball->setDirection( _ballStartingDirection);
    _ball->setMinVelocity(550);
    _ball->setMaxVelocity(int(VisibleRect::top().y));
    this->addChild(_ball);

    //////////////////////////////

    int bricksPerLine = 1;  //max = 16
    int bricksLineCount = 1;    //max = 10
    Vector<Brick*> bricksM( bricksPerLine * bricksLineCount);
    for(int i=0; i < bricksPerLine; i++)
    {
        for(int j=0; j < bricksLineCount; j++) {
            Brick *brick = Brick::createWithTexture("res/brick.png");
            brick->setColor(Color3B(random(0,255),random(0,255),random(0,255)));
            brick->setPosition(VisibleRect::left().x + 45 + i * 90, VisibleRect::center().y + 60 + j * 35);
            bricksM.pushBack(brick);
        }
    }
    _bricks = bricksM;
    for (auto& brick : _bricks)
    {
        addChild(brick);
    }

    //////////////////////////////

    schedule( CC_SCHEDULE_SELECTOR(GameScene::doStep) );

    return true;
}


void GameScene::doStep(float delta)
{
    _ball->move(delta);

    if(_ball->collideWithPaddle( _paddle ))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/jump.wav", false, 1.0f, 1.0f, 1.0f);
    }

    for( auto it = _bricks.begin(); it != _bricks.end(); it++)
    {
        if(_ball->collideWithBrick(*it))
        {
            _score++;
            removeChild(*it);
            _bricks.erase(it);

            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/hit.wav", false, 1.0f, 1.0f, 1.0f);
            CCLOG("Delete Brick");

            if(_bricks.size() == 0) 
            {
                CCLOG("WINNER WINNER CHICKEN DINNER" );
                CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
                Director::getInstance()->replaceScene(
                        TransitionFade::create(0.5, GameOverScene::createScene(), Color3B(255, 0, 0)));
            }
            break;
        }
    }

    if(_ball->collideWithBottom())
    {
        _lifes--;
        _ball->setPosition(VisibleRect::center());
        _ball->setVelocity(_ballStartingVelocity);
        _ball->setDirection(_ballStartingDirection);

        if (_lifes <= 0)
        {
            _ball->setVelocity(0);
            CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
            Director::getInstance()->replaceScene(
                    TransitionFade::create(0.5, GameOverScene::createScene(), Color3B(255, 0, 0)));
        }
    }
}