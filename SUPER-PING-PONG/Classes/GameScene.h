#pragma once
#include "cocos2d.h"

using namespace cocos2d;


class GameScene : public cocos2d::Scene
{

    Size _screenSize;

public:
    static Scene* createScene();

    virtual bool init();


    CREATE_FUNC(GameScene);

};