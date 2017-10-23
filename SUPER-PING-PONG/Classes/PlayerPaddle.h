#include "cocos2d.h"
using namespace cocos2d;
class PlayerPaddle : public Sprite
{
public:
    float sizeX = 1.0;
    float sizeY = 1.0;
    static PlayerPaddle* createPlayerPaddle();
    float incPaddleBonus();
    float decPaddleBonus();
};