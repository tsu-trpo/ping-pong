#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Brick : public Sprite {
public:
    std::vector<Vector<Brick *>> *_bricks;
    int _line, _column;

    void initBrick(std::vector<Vector<Brick *>> *bricks, int newLine, int newColumn);
    Rect getRect();
    Rect getBox();

    float getWidth();
    void setWidth(float newWidth);

    float getHeight();
    void setHeight(float newHeight);
    /*булево значение отображает разбился кубик или нет,
     * нужно для бонусов*/
    virtual bool onContact() = 0;
};
