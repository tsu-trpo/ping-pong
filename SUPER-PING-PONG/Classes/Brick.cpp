#include <Brick.h>

Brick* Brick::createWithTexture(std::string textureName) {
    Brick* self = new (std::nothrow) Brick();
    self->initWithFile(textureName);
    self->autorelease();

    return self;
}

Rect Brick::getBox() {

}