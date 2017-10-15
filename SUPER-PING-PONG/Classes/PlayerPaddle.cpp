#include "PlayerPaddle.h"
PlayerPaddle * PlayerPaddle::createPlayerPaddle() {

    PlayerPaddle *self = NULL;
    self = new PlayerPaddle();
    self->initWithFile("paddle.png");
    return self;
}