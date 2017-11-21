#include <Brick.h>

Brick* Brick::createWithTexture(std::string textureName) {
    Brick* self = new (std::nothrow) Brick();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

Rect Brick::getRect()
{
    return Rect(
            -(getContentSize().width * getScaleX() * 0.5),
            -(getContentSize().height * getScaleY() * 0.5),
            getContentSize().width * getScaleX(),
            getContentSize().height * getScaleY());
}

Rect Brick::getBox() {
    auto box = getRect();
    box.origin.x += getPosition().x; //setting rect to it's real position
    box.origin.y += getPosition().y;
    return box;

}

float Brick::getWidth() {
    return getContentSize().width * getScaleX();

}

float Brick::getHeight() {
    return getContentSize().height * getScaleY();
}