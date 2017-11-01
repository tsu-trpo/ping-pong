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
    _lifes = 3;
    _score = 0;
    _currentLevel = 0;

    //////////////////////////////

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bg_1.ogg", true);
    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    this->addChild(bg);

    //////////////////////////////

    _scoreLabel = Label::createWithTTF("Score: " + std::to_string(_score * 10), "fonts/arial.ttf", 30);
    _scoreLabel->setPosition(VisibleRect::leftTop());
    _scoreLabel->setAnchorPoint(Vec2(0,1));
    this->addChild(_scoreLabel);

    _lifesLabel = Label::createWithTTF("Lifes: " + std::to_string(_lifes), "fonts/arial.ttf", 30);
    _lifesLabel->setPosition(VisibleRect::rightTop());
    _lifesLabel->setAnchorPoint(Vec2(1,1));
    this->addChild(_lifesLabel);

    //////////////////////////////

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + _screenSize.height * 0.07));
    _paddle->setScaleX(1.2);

    this->addChild(_paddle);

    //////////////////////////////

    _ballStartingDirection = Vec2(0, -1);
    _ballStartingVelocity = 300;
    _ball = Ball::createWithTexture("res/ball.png");
    _ball->setPosition( VisibleRect::center() );
    _ball->setVelocity( _ballStartingVelocity );
    _ball->setDirection( _ballStartingDirection);
    _ball->setMinVelocity(550);
    _ball->setMaxVelocity(int(VisibleRect::top().y));
    this->addChild(_ball);

    //////////////////////////////

    buildWall(_currentLevel);

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
            CCLOG("Delete Brick");
            removeChild(*it);
            _bricks.erase(it);
            //it--;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/hit.wav", false, 1.0f, 1.0f, 1.0f);

            _score++;
            _scoreLabel->setString("Score: " + std::to_string(_score * 10));

            if(_bricks.size() == 0)
            {
                CCLOG("WINNER WINNER CHICKEN DINNER" );
                _currentLevel++;
                buildWall(_currentLevel);

                _ball->setPosition(VisibleRect::center());
                _ball->setVelocity(_ballStartingVelocity);
                _ball->setDirection(_ballStartingDirection);
            }
            break;
        }
    }

    if(_ball->collideWithBottom())
    {
        _lifes--;
        _lifesLabel->setString("Lifes: " + std::to_string(_lifes));
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


void GameScene::buildWall(int levelNo)
{
    char** levels = new char*[10]; // levels count
    for(int i = 0; i< 10; i++)
    {
        levels[i] = new char[161]; // bricks count
    }

    levels[0] = "0000000000000000000001111110000000001222222100000001222222221000001222222222210000122222222221000001222222221000000012222221000000000111111000000000000000000000";
    levels[1] = "2200000000000000222200000000000022222200000000002222222200000000222222222200000022222222222200002222222222222200222222222222222211111111111111111111111111111111";
    levels[2] = "0111010001110002001001000100100200100100010010020111011101110002000000000000000200011100011100020001010001001002000111000111000200010100010010022222222222222222";
    levels[3] = "0000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000";
    levels[4] = "0000000000000000000001111110000000001222222100000001222222221000001222222222210000122222222221000001222222221000000012222221000000000111111000000000000000000000";
    levels[5] = "2200000000000000222200000000000022222200000000002222222200000000222222222200000022222222222200002222222222222200222222222222222211111111111111111111111111111111";
    levels[6] = "0111010001110002001001000100100200100100010010020111011101110002000000000000000200011100011100020001010001001002000111000111000200010100010010022222222222222222";

    int columnN = 16;  //max = 16
    int lineN = 10;    //max = 10
    Vector<Brick*> bricksM;

    for(int line = 0; line < lineN; line++)
    {
        for(int column = 0; column < columnN; column++)
        {
            switch (levels[levelNo][ columnN * line + column ])
            {
                case '0':
                {
                    CCLOG("WHITE");
                    break;
                }
                case '1':
                {
                    CCLOG("PINK");
                    Brick *brick = Brick::createWithTexture("res/brick.png");
                    brick->setColor(Color3B::GREEN);
                    brick->setPosition(VisibleRect::left().x + 45 + column * 90, VisibleRect::top().y - 100- line * 35);

                    bricksM.pushBack(brick);
                    break;
                }
                case '2':
                {
                    CCLOG("GREEN");
                    Brick *brick = Brick::createWithTexture("res/brick.png");
                    brick->setColor(Color3B(random(0,255),random(0,255),random(0,255)));
                    brick->setPosition(VisibleRect::left().x + 45 + column * 90, VisibleRect::top().y - 100 - line * 35);
                    bricksM.pushBack(brick);
                    break;
                }
            }
        }
    }
    _bricks = bricksM;
    for (auto& brick : _bricks)
    {
        addChild(brick);
    }
}
