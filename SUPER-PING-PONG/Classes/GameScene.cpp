#include "GameScene.h"
USING_NS_CC;
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    // super init first
    if ( !Layer::init() )
    {
        return false;
    }
    screenSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    auto *bg = Sprite::create("pongBG.png");
    bg->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(bg);

    pongBall = Ball::createBall();
    pongBall->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.5));
    this->addChild(pongBall);
    playerPaddle = PlayerPaddle::createPlayerPaddle();
    playerPaddle->setPosition(Vec2(origin.x + screenSize.width * 0.05, origin.y + screenSize.height * 0.5));
    this->addChild(playerPaddle);
    opponentPaddle = Sprite::create("paddle.png");
    opponentPaddle->setPosition(Vec2(origin.x + screenSize.width * 0.95, origin.y + screenSize.height * 0.5));
    this->addChild(opponentPaddle);

    int textSize = 0;
    textSize = 40;
    startText = Label::createWithTTF("First to 5 Wins", "fonts/arial.ttf", textSize);
    startText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.8));
    this->addChild(startText);
    int scoreLabelSize = 0;
    scoreLabelSize = 40;

    playerScoreLabel = Label::createWithTTF("Player Score: 0", "fonts/arial.ttf", scoreLabelSize);
    playerScoreLabel->setPosition(Vec2(origin.x + screenSize.width * 0.2, origin.y + screenSize.height * 0.95));
    this->addChild(playerScoreLabel);
    opponentScoreLabel = Label::createWithTTF("Opponent Score: 0", "fonts/arial.ttf", scoreLabelSize);
    opponentScoreLabel->setPosition(Vec2(origin.x + screenSize.width * 0.8, origin.y + screenSize.height * 0.95));
    this->addChild(opponentScoreLabel);
    playerScore = 0;
    opponentScore = 0;
    gameHasStarted = false;
    ballDirection = Vec2(0, 0);
    ballVelocity = screenSize.width * 0.5;

    /*
    //Simple play without score
    startText = Label::createWithTTF("Tap to Start", "fonts/arial.ttf", 50);
    startText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.8));
    this->addChild(startText);
    gameHasStarted = false;
    ballDirection = Vec2(0, 0);
    ballVelocity = 300;
    */

    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    eventListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    eventListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, playerPaddle);

    return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    if (!gameHasStarted) {
        //remove label
        this->removeChild(startText);
        startText = NULL;
        //start the ball in a random direction
        pongBall->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y +         screenSize.height * 0.5));

        int startLeft = 0;
        float randStart = CCRANDOM_0_1();
        if (randStart < 0.5) {
            startLeft = 1;
        }
        float randStartPercentage = CCRANDOM_0_1() * 90 - 45;
        float startAngleInDegrees = startLeft * 180 + randStartPercentage;
        float xDirectionPos = cosf(CC_DEGREES_TO_RADIANS(startAngleInDegrees));
        float yDirectionPos = sinf(CC_DEGREES_TO_RADIANS(startAngleInDegrees));
        ballDirection = Vec2(xDirectionPos, yDirectionPos);

        //ballDirection = Vec2(1, 1);
        this->scheduleUpdate();
        gameHasStarted = true;
    } else {
        Vec2 touchLocation = touch->getLocation();
        //make sure paddle can't go off screen
        float paddleY = MIN(MAX(touchLocation.y, origin.y + playerPaddle->getContentSize().height * 0.5 ), origin.y + screenSize.height - playerPaddle->getContentSize().height * 0.5 );
        playerPaddle->setPosition(Vec2(playerPaddle->getPosition().x, paddleY));
    }
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    Vec2 touchLocation = touch->getLocation();
    //make sure paddle can't go off screen
    float paddleY = MIN(MAX(touchLocation.y, origin.y + playerPaddle->getContentSize().height * 0.5 ), origin.y + screenSize.height - playerPaddle->getContentSize().height * 0.5 );
    playerPaddle->setPosition(Vec2(playerPaddle->getPosition().x, paddleY));
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
    //nothing for now
}
void GameScene::onTouchCancelled(Touch *touch, Event *unused_event) {
    //nothing for now
}

void GameScene::update(float delta) {
    //find new opponent paddle position
    float paddleY = MIN(MAX(MAX(MIN(pongBall->getPosition().y, opponentPaddle->getPosition().y + screenSize.height * 0.01), opponentPaddle->getPosition().y - screenSize.height * 0.01), origin.y + opponentPaddle->getContentSize().height * 0.5), origin.y + screenSize.height - opponentPaddle->getContentSize().height * 0.5 );

    //float paddleY = MIN(MAX(pongBall->getPosition().y, origin.y + opponentPaddle->getContentSize().height * 0.5), origin.y + screenSize.height - opponentPaddle->getContentSize().height * 0.5 );
    opponentPaddle->setPosition(Vec2(opponentPaddle->getPosition().x, paddleY));
    //find new ball position
    Vec2 newPosition = pongBall->getPosition() + ballDirection * ballVelocity * delta;
    if (newPosition.y < origin.y || newPosition.y > origin.y + screenSize.height) {
        //reverse y direction of the ball
        ballDirection = Vec2(ballDirection.x, -ballDirection.y);
        newPosition = Vec2(newPosition.x, pongBall->getPosition().y + ballDirection.y * ballVelocity * delta);
    }

    pongBall->setPosition(newPosition);
    if ((playerPaddle->getBoundingBox().intersectsRect(pongBall->getBoundingBox()) && ballDirection.x < 0) || (opponentPaddle->getBoundingBox().intersectsRect(pongBall->getBoundingBox()) && ballDirection.x > 0)) {
//reverse x direction of the ball & y direction based on paddle hit later
        Sprite *contactPaddle = playerPaddle;
        float newDirectionIsLeft = false;
        if (opponentPaddle->getBoundingBox().intersectsRect(pongBall->getBoundingBox())) {
            contactPaddle = opponentPaddle;
            newDirectionIsLeft = true;
        }
        float percentageHeightOfBallOnPaddle = (pongBall->getPosition().y - contactPaddle->getPosition().y + contactPaddle->getContentSize().height * 0.5) / contactPaddle->getContentSize().height;
        float ballDirectionDegree = 0;
        if (newDirectionIsLeft) {
            ballDirectionDegree = 225 - (percentageHeightOfBallOnPaddle * 90);
        } else {
            ballDirectionDegree = -45 + (percentageHeightOfBallOnPaddle * 90);
        }
        float xDirectionPos = cosf(CC_DEGREES_TO_RADIANS(ballDirectionDegree));
        float yDirectionPos = sinf(CC_DEGREES_TO_RADIANS(ballDirectionDegree));
        ballDirection = Vec2(xDirectionPos, yDirectionPos);
        ballVelocity = MIN(ballVelocity * 1.05, screenSize.width);
        newPosition = Vec2(pongBall->getPosition().x + ballDirection.x * ballVelocity * delta, newPosition.y);
    }

    if (newPosition.x < origin.x + 0) {

        //point over--enemy wins int textSize = 0;
        int textSize = 0;
            textSize = 40;
        opponentScore++;
        std::string middleText;
        if (opponentScore < 5) {
            middleText = "Tap to Start";
        } else {
            middleText = "You Lose";
            playerScore = 0;
            opponentScore = 0;
        }
        startText = Label::createWithTTF(middleText, "fonts/arial.ttf", textSize);

        startText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y + screenSize.height * 0.8));
        this->addChild(startText);

        std::stringstream ss;
        ss << playerScore;
        std::string playerScoreString = ss.str();
        std::string playerString = "Player Score: " + playerScoreString;
        playerScoreLabel->setString(playerString.c_str());
        std::stringstream ss2;
        ss2 << opponentScore;
        std::string opponentScoreString = ss2.str();
        std::string opponentString = "Opponent Score: " + opponentScoreString;
        opponentScoreLabel->setString(opponentString.c_str());

        gameHasStarted = false;
        ballDirection = Vec2(0, 0);
        ballVelocity = screenSize.width * 0.5;
        this->unscheduleUpdate();
    } else if (newPosition.x > origin.x +  screenSize.width) {
        //point over--player wins
        int textSize = 0;
            textSize = 40;
        playerScore++;
        std::string middleText;
        if (playerScore < 5) {
            middleText = "Tap to Start";
        } else {
            middleText = "You Win";
            playerScore = 0;
            opponentScore = 0;
        }
        startText = Label::createWithTTF(middleText, "fonts/arial.ttf", textSize);
        startText->setPosition(Vec2(origin.x + screenSize.width * 0.5, origin.y +         screenSize.height * 0.8));
        this->addChild(startText);

        std::stringstream ss;
        ss << playerScore;
        std::string playerScoreString = ss.str();
        std::string playerString = "Player Score: " + playerScoreString;
        playerScoreLabel->setString(playerString.c_str());
        std::stringstream ss2;
        ss2 << opponentScore;
        std::string opponentScoreString = ss2.str();
        std::string opponentString = "Opponent Score: " + opponentScoreString;
        opponentScoreLabel->setString(opponentString.c_str());

        gameHasStarted = false;
        ballDirection = Vec2(0, 0);
        ballVelocity = screenSize.width * 0.5;
        this->unscheduleUpdate();
    }
}