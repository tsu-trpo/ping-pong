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
    _screenSize = Director::getInstance()->getVisibleSize();


    // DEBUG
    //_ballStartingVelocity = Vec2(100.0f, 0.0f) * 4;
    _ballStartingDirection = Vec2(0, -1);
    _ballStartingVelocity = 300;
    _lifes = 3;
    _score = 0;

    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    this->addChild(bg);

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + _screenSize.height * 0.1));
    this->addChild(_paddle);

    _ball = Ball::createWithTexture("res/ball.png");
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    _ball->setDirection( _ballStartingDirection);
    this->addChild(_ball);

    int bricksPerLine = 16;
    int bricksLineCount = 10;

    Vector<Brick*> bricksM( bricksPerLine * bricksLineCount);

    for(int i=0; i < bricksPerLine; i++)
    {
        for(int j=0; j < bricksLineCount; j++) {
            Brick *brick = Brick::createWithTexture("res/brick.png");
            brick->setPosition(VisibleRect::left().x + 45 + i * 90, VisibleRect::center().y + 100 + j * 35);
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



    _ball->collideWithPaddle( _paddle );

    for( auto it = _bricks.begin(); it != _bricks.end(); it++)
    {
        if(_ball->collideWithBrick(*it))
        {
            _score++;
            removeChild(*it);
            _bricks.erase(it);
            //it = _bricks.end() - 1;
            CCLOG("Delete Brick, left: %d", _bricks.size() );
        }
    }

    if(_ball->collideWithBottom())
    {
        _lifes--;
        if (_lifes <= 0)
        {
            _ball->setVelocity(0);
            Director::getInstance()->replaceScene(
                    TransitionFade::create(0.5, GameOverScene::createScene(), Color3B(255, 0, 0)));
        } else
        {
            _ball->setPosition(VisibleRect::center());
            _ball->setVelocity(_ballStartingVelocity);
            _ball->setDirection(_ballStartingDirection);
        }

    }
}