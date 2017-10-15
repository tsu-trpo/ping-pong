#include "PlayerPaddle.h"
PlayerPaddle * PlayerPaddle::createPlayerPaddle() {
    PlayerPaddle *self = NULL;
    self = new PlayerPaddle();
    if (self && self->initWithFile("paddle.png")) {
        //nothing for now
    } else {
        delete self;
    }
    return self;
}