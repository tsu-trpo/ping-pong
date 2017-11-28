#include "GameScene.h"
#include "AudioPlayer.h"
#include "VisibleRect.h"


Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    scene->getPhysicsWorld()->setDebugDrawMask(0xffff);

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

    AudioPlayer::playBackgroundMusic();

    auto *bg = Sprite::create("res/pongBG.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);

    /// World boundaries ///

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.1f, 1.0f, 0.0f), 5);
    edgeBody->setDynamic(false);

    auto edgeNode = Node::create();
    edgeNode->setPosition(VisibleRect::center());
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    /// Paddle ///

    _paddle = Paddle::createWithTexture("res/paddle.png");
    _paddle->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y + VisibleRect::top().y * 0.07));
    _paddle->setScaleX(1.2);

    addChild(_paddle);

    /// Balls ///

    Vec2 ballStartPosition = Vec2(VisibleRect::center().x, VisibleRect::center().y);
    Vec2 ballStartVelocity = Vec2(0,-500);

    _balls.pushBack(Ball::createWithTexture("res/ball.png", ballStartPosition, ballStartVelocity));
    addChild(_balls.at(0));

    return true;
}
