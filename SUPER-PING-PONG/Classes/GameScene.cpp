#include "GameScene.h"
#include "VisibleRect.h"

USING_NS_CC;

using namespace cocos2d;


Scene* GameScene::createScene() {
    auto scene = GameScene::create();

    auto layer = KeyboardScene::create();

}


bool GameScene::init()
{
    if ( !Scene::init() ) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("background.jpg");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

    auto ball = Sprite::create("ball.png");
    ball->setPosition( VisibleRect::center() );
    this->addChild(ball);

    auto paddle1 = Sprite::create("paddle.png");
    paddle1->setPosition(VisibleRect::right());
    this->addChild(paddle1);

    auto paddle2 = Sprite::create("paddle.png");
    paddle2->setPosition(VisibleRect::left());
    this->addChild(paddle2);

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

        switch(keyCode) {
            case EventKeyboard::KeyCode::KEY_O:
                auto y = getPosition().y + 0.1;
                paddle1->setPosition(VisibleRect::rightTop());
                break;
            case EventKeyboard::KeyCode::KEY_L:
                break;
            default:
                break;
        }

    };


}
