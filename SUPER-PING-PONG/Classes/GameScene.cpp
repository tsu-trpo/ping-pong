#include "GameScene.h"
#include "AudioPlayer.h"
#include "VisibleRect.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

void GameScene::createBricks(int lines, int columns)
{
    _bricks = std::vector<std::vector<Brick*>>(lines);
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;

    float widthBrick = 90;
    float heightBrick = 35;

    int oneSide = columns/2;
    bool uneven = columns%2;
    float beginString = center - widthBrick*oneSide - (widthBrick*uneven)/2 + widthBrick/2;
    float y = top - heightBrick/2 - heightBrick*1.5;

    for(int j = 0; j < lines; j++)
    {
        float x = beginString;
        for (int i = 0; i < columns; i++)
        {
            Brick* br = Brick::createWithTexture("res/brick.png");
            log("add brick");
            br->setWidth(widthBrick);
            br->setHeight(heightBrick);
            br->setPosition(x, y);
            addChild(br);
            _bricks.at(j).push_back(br);
            x += widthBrick;
        }
        y -= heightBrick;
    }
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    /// Background ///

    AudioPlayer::playBackgroundMusic();

    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);


    /// Paddle ///

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + VisibleRect::top().y * 0.07));
    _paddle->setScaleX(1.2);

    addChild(_paddle);

    /// Balls ///

    Vec2 ballStartPosition = Vec2(VisibleRect::center().x, VisibleRect::center().y);
    Vec2 ballStartDirection = Vec2(0,-1);
    int ballStartVelocity = 300;

    _balls.pushBack(Ball::createWithTexture("res/ball.png", ballStartPosition, ballStartDirection, ballStartVelocity));
    addChild(_balls.at(0));

    ///Bricks///

    createBricks(2,7);

    /// Update method ///

    schedule( CC_SCHEDULE_SELECTOR(GameScene::update) );

    return true;
}


void GameScene::update(float delta)
{
    for(auto ball : _balls)
    {
        ball->move(delta);
        ball->collideWithPaddle( _paddle );

        for( auto str = _bricks.begin(); str != _bricks.end(); str++)
        {
            for( auto clmn = (*str).begin(); clmn != (*str).end(); clmn++)
            {
                if(ball->collideWithBrick(*clmn))
                {
                    CCLOG("Delete Brick");
                    if(_bricks.size() == 0)
                    {
                        CCLOG("WINNER WINNER CHICKEN DINNER");
                    }
                }
            }
        }

        if(ball->collideWithBottom())
        {
            AudioPlayer::playEffect(AudioPlayer::lose);
            ball->respawn();
            CCLOG("BETTER LUCK NEXT TIME" );
        }
    }
}
