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
    _bricks = std::vector<Vector<Brick*>>(lines);
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;

    float widthBrick = 90;
    float heightBrick = 35;

    float halfLine = (columns/2.0)*widthBrick;
    float beginLine = center - halfLine + widthBrick/2;
    float offsetTop = 1.5*heightBrick;
    float y = top - offsetTop + heightBrick/2;

    for(int j = 0; j < lines; j++)
    {
        float x = beginLine;
        for (int i = 0; i < columns; i++)
        {
            Brick* brick = Brick::createWithTexture("res/brick.png");
            brick->setWidth(widthBrick);
            brick->setHeight(heightBrick);
            brick->setPosition(x, y);
            addChild(brick);
            _bricks.at(j).pushBack(brick);
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

        for( auto line = _bricks.begin(); line != _bricks.end(); line++)
        {
            for( auto column= line->begin(); column != line->end(); column++)
            {
                if(ball->collideWithBrick(**column))
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
