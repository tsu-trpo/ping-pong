#include "GameScene.h"
#include "VisibleRect.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

void GameScene::createBricks(int perLine, int perColumn, std::string textureName)
{
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;
    _bricks = Vector<Brick*>(perLine*perColumn);

    Brick *br = Brick::createWithTexture(textureName);
    float widthBrick = br->getWidth();
    float heightBrick = br->getHeight();
    int oneside = perLine/2;

    int flag = perLine%2; //если четное

    float x = center - widthBrick*oneside - (widthBrick*flag)/2 + widthBrick/2;
    float y = top - heightBrick/2 - heightBrick*1.5;


    for(int j = 0; j < perColumn; j++)
    {
        for (int i = 0; i < perLine; i++)
        {
            Brick* brTemp = Brick::createWithTexture(textureName);
            log("add");
            brTemp->setPosition(x, y);
            addChild(br);
            _bricks.pushBack(brTemp);
            x += widthBrick;

        }
        y -= heightBrick;
        x = center - widthBrick * oneside - (widthBrick * flag) / 2 + widthBrick / 2;
    }
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    /// Background ///

    //Todo play bg music

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

    createBricks(7,2, "res/brick.png");

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

        for( auto it = _bricks.begin(); it != _bricks.end(); it++)
        {
            if (ball->collideWithBrick(*it))
            {
                CCLOG("Delete Brick");

                if(_bricks.size() == 0)
                {
                    CCLOG("WINNER WINNER CHICKEN DINNER" );
                }
            }
        }

        if(ball->collideWithBottom())
        {
            ball->respawn();
            CCLOG("BETTER LUCK NEXT TIME" );
        }
    }
}
