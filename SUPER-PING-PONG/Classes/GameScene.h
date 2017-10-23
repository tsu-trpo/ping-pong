#pragma once
#ifndef GameScene_hpp
#define GameScene_hpp
#include "cocos2d.h"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "VisibleRect.h"
#include "Brick.h"
#include <Box2D/Box2D.h>
using namespace cocos2d;
class GameScene : public cocos2d::Layer
{
public:
    Vector <Brick *> bricks;
    Brick *testSprite;
    Ball *pongBall;
    PlayerPaddle *playerPaddle;
    Sprite *opponentPaddle;
    Label *startText;
    Label *playerScoreLabel;
    Label *opponentScoreLabel;
    int playerScore;
    int opponentScore;
    bool gameHasStarted;
    Vec2 ballDirection;
    int ballVelocity;
    Size screenSize;
    Vec2 origin;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float delta);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};
#endif // __GAMESCENE_SCENE_H__