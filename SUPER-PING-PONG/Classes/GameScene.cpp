#include "GameScene.h"
#include "AudioPlayer.h"
#include "DefaultMaterial.h"
#include "VisibleRect.h"

const int debugDrawAllMask = 0xffff;

Scene *GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(debugDrawAllMask);

    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    _wall = new BricksWall();
    if (!Layer::init()) {
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
    Vec2 ballStartVelocity = Vec2(0, -500);

    _balls.pushBack(Ball::createWithTexture("res/ball.png", ballStartPosition, ballStartVelocity));
    addChild(_balls.at(0));

    /// Bricks///

    _wall->createBricks(10, 15, this);

    return true;
}
