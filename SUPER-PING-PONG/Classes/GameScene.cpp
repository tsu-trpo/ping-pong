#include "GameScene.h"
#include "VisibleRect.h"

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

    unsigned int perLine = 7;
    unsigned int perColumn = 2;
    float center = VisibleRect::center().x;
    float top = VisibleRect::top().y;
    _bricks = Vector<Brick*>(perLine*perColumn);
    for(unsigned int i = 0; i < (perLine*perColumn); i++) {
        Brick* br = Brick::createWithTexture("res/brick.png");
        addChild(br);
        _bricks.pushBack(br);
    }

    float width_of_brick = _bricks.at(0)->getContentSize().width * _bricks.at(0)->getScaleX();
    float height_of_brick = _bricks.at(0)->getContentSize().height * _bricks.at(0)->getScaleY();
    unsigned int oneside = perLine/2;

    int flag = perLine%2; //если четное

    float x = center - width_of_brick*oneside - (width_of_brick*flag)/2 + width_of_brick/2;
    float y = top - height_of_brick/2;

    int k = 0;
    for(int j = 0; j < perColumn; j++) {
        for (int i = 0; i < perLine; i++) {
            log("add");
            _bricks.at(k)->setPosition(x, y-10);
            x += width_of_brick;
            k++;
        }
        y -= height_of_brick;
        x = center - width_of_brick*oneside - (width_of_brick*flag)/2 + width_of_brick/2;
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
        ball->collideWithPaddle( _paddle );

      /*  for( auto it = _bricks.begin(); it != _bricks.end(); it++)
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
*/
        if(ball->collideWithBottom())
        {
            ball->respawn();
            CCLOG("BETTER LUCK NEXT TIME" );
        }
    }
}
