#include "VisibleRect.h"
#include "ball.h"

Ball* Ball::createWithTexture(std::string textureName) {
    Ball* self = new (std::nothrow) Ball();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

void Ball::setDirection(Vec2 direction) {
    direction_m = direction;
}

Vec2 Ball::getDirection() {
    return direction_m;
};

void Ball::setVelocity(int velocity) {
    velocity_m = velocity;
}

float Ball::getRadius() {
    return this->getScale()/2;
}

void Ball::move(float delta) {

    this->setPosition(getPosition() + direction_m * velocity_m);
    this->setRotation(this->getRotation() + 1);

    if (getPosition().x > VisibleRect::right().x - getRadius()) {
        setPosition(VisibleRect::right().x, getPosition().y);
        direction_m.x *= -1;
    }
    else if (getPosition().x < VisibleRect::left().x - getRadius()) {
        setPosition(VisibleRect::left().x, getPosition().y);
        direction_m.x *= -1;
    }
    else if (getPosition().y > VisibleRect::top().y - getRadius()) {
        setPosition(getPosition().x, VisibleRect::top().y);
        direction_m.y *= -1;
    }
    else if (getPosition().y < VisibleRect::bottom().y - getRadius()) {
        setPosition(VisibleRect::center());
    }
}

bool Ball::collideWithPaddle(Paddle* paddle) {
    auto center_of_paddle = paddle->getPosition().x;
    auto half_length = paddle->getContentSize().width/2;
    auto positionX = getPosition().x;
    auto positionY = getPosition().y;
    if((center_of_paddle - half_length) < positionX) {
        if(positionX < center_of_paddle + half_length) {
            if(positionY < (paddle->getPosition().y + paddle->getContentSize().height + getRadius())){

                float new_direction = ((center_of_paddle - positionX) / half_length)*(-1);
                setPosition(positionX, paddle->getPosition().y + getRadius() + paddle->getContentSize().height);
                setDirection(Vec2(new_direction,1));

                return true;
            }
        }
    }
    return false;
}

bool Ball::collideWithBrick(Brick *brick) {
    auto positionX = getPosition().x;
    auto positionY = getPosition().y;

    float width_of_brick = brick->getContentSize().width * brick->getScaleX();
    float height_of_brick = brick->getContentSize().height * brick->getScaleY();


    if(positionX < brick->getPosition().x + width_of_brick/2) {
        if(brick->getPosition().x - width_of_brick/2 < positionX) {
            if(positionY > brick->getPosition().y - height_of_brick/2) {
                if(positionY < brick->getPosition().y + height_of_brick/2) {
                    direction_m.y *= -1;
                    setPosition(positionX, brick->getPosition().y + direction_m.y * (width_of_brick / 2));
                    return true;
                }

            }
        }
    }

    return false;
}


