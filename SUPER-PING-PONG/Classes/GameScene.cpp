#include <iostream>
#include "GameScene.h"
#include "AudioPlayer.h"
#include "VisibleRect.h"
#include "DefaultMaterial.h"


const int debugDrawAllMask = 0xffff;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    scene->getPhysicsWorld()->setDebugDrawMask(debugDrawAllMask);

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

    /// World boundaries ///

    Size visibleSize = Director::getInstance()->getVisibleSize();
    const int edgeBorder = 5;
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, defaultMaterial, edgeBorder);
    edgeBody->setDynamic(false);

    auto edgeNode = Node::create();
    edgeNode->setPosition(VisibleRect::center());
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    /// Paddle ///

    const float bottomMarginY = VisibleRect::top().y * 0.07;

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + bottomMarginY));
    _paddle->setScaleX(1.2);

    addChild(_paddle);

    /// Balls ///

    Vec2 ballStartPosition = Vec2(VisibleRect::center().x, VisibleRect::center().y);
    Vec2 ballStartVelocity = Vec2(0,-500);

    _balls.pushBack(Ball::createWithTexture("res/ball.png", ballStartPosition, ballStartVelocity));
    addChild(_balls.at(0));

    /// Bricks ///

    createBricks(2,7);

    /// Contact detecting ///

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::ContactBallBrick, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

bool GameScene::ContactBallBrick(PhysicsContact& contact)
{
    Node *brick = nullptr;
    Node *ball = nullptr;

    if (contact.getShapeA()->getBody()->getName() == "brick" &&
        contact.getShapeB()->getBody()->getName() == "ball")
    {
        brick = contact.getShapeA()->getBody()->getNode();
        ball = contact.getShapeB()->getBody()->getNode();
    }
    else if (contact.getShapeA()->getBody()->getName() == "ball" &&
             contact.getShapeB()->getBody()->getName() == "brick")
    {
        brick = contact.getShapeB()->getBody()->getNode();
        ball = contact.getShapeA()->getBody()->getNode();
    }

    if (ball && brick)
    {
        CCLOG("Collide: ball + brick");
        GameScene::dropBonus(brick);
    }
    return true;
}

bool GameScene::dropBonus(Node *brick)
{
    Vec2 bonusStartPosition = Vec2(VisibleRect::center().x, VisibleRect::center().y);
    Vec2 bonusStartVelocity = Vec2(0,-300);

    Bonus* bonus = Bonus::createWithTexture("res/bonus.png", bonusStartPosition, bonusStartVelocity);
    bonus->setBonusPosition(brick, bonus);
    addChild(bonus);
}