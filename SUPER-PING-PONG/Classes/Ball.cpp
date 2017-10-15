#include "Ball.h"
Ball * Ball::createBall() {
    Ball *self = NULL;
    self = new Ball();
    if (self && self->initWithFile("ball.png")) {
        //nothing for now
    } else {
        delete self;
    }
    return self;
}