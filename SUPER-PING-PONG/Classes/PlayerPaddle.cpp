#include <iostream>
#include "PlayerPaddle.h"
PlayerPaddle * PlayerPaddle::createPlayerPaddle() {

    PlayerPaddle *self = NULL;
    self = new PlayerPaddle();
    self->initWithFile("paddle.png");
    return self;
}

float PlayerPaddle::incPaddleBonus() {
    if (sizeY < 5) {
        sizeY += 0.5;
        std::cout << "current paddle size: " << sizeY << std::endl;
    }
    else {
        std::cout << "max size is reached" << std::endl;
    }
    return sizeY;
}

float PlayerPaddle::decPaddleBonus() {
    if (sizeY > 0.3) {
        sizeY -= 0.2;
        std::cout << "current paddle size: " << sizeY << std::endl;
    }
    else {
        std::cout << "min size is reached" << std::endl;
    }
    return sizeY;
}