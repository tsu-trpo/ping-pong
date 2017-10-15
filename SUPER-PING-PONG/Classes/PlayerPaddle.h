#ifndef PlayerPaddle_h
#define PlayerPaddle_h
#include "cocos2d.h"
using namespace cocos2d;
class PlayerPaddle : public Sprite
{
public:
    static PlayerPaddle* createPlayerPaddle();
};
#endif // __PlayerPaddle_SCENE_H__