#include "cocos2d.h"
#pragma once

class GameOverScene : public cocos2d::Layer
{

public:
    virtual bool init();

    static cocos2d::Scene *createScene();

    void startAgainCallback(cocos2d::Ref *pSender);


    CREATE_FUNC(GameOverScene);

};