#include "GameOverScene.h"
//#include "ui/UIDeprecated.h"
#include "GameScene.h"

//using namespace std;
//using namespace cocos2d;
//using namespace cocos2d::ui;

//USING_NS_CC;


Scene *GameOverScene::createScene()
{
    auto scene = Scene::create();

    GameOverScene* layer = GameOverScene::create();

    scene->addChild(layer);
    return scene;
}



bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }


    Size _screenSize = Director::getInstance()->getVisibleSize();



    auto gameOverLabel = Label::createWithTTF("Game over!", "fonts/arial.ttf", 24);
    gameOverLabel->setTextColor(Color4B::WHITE);


    auto startAgainLabel = Label::createWithTTF("Play again", "fonts/arial.ttf", 30);
    startAgainLabel->setTextColor(Color4B::ORANGE);

    auto playAgainItem = MenuItemLabel::create(startAgainLabel,
                                               CC_CALLBACK_1(GameOverScene::startAgainCallback, this));
    auto menu = Menu::create(playAgainItem, NULL);


    gameOverLabel->setPosition(_screenSize.width/2, _screenSize.height/2 + gameOverLabel->getContentSize().height * 3);
    menu->setPosition(_screenSize.width/2, gameOverLabel->getPosition().y - gameOverLabel->getContentSize().height);

    this->addChild(gameOverLabel);
    this->addChild(menu);

    return true;
}


void GameOverScene::startAgainCallback(Ref *pSender)
{
    Director::getInstance()->replaceScene(
            TransitionFade::create(0.5, GameScene::createScene(), Color3B(255, 255, 255)));
}

