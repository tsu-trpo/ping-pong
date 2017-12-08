#include "VisibleRect.h"

using namespace cocos2d;

Rect VisibleRect::sVisibleRect;

void VisibleRect::lazyInit()
{
    // no lazy init
    // Useful if we change the resolution in runtime
    sVisibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect()
{
    lazyInit();
    return sVisibleRect;
}

Vec2 VisibleRect::left()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x,
                sVisibleRect.origin.y+sVisibleRect.size.height/2);
}

Vec2 VisibleRect::right()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width,
                sVisibleRect.origin.y+sVisibleRect.size.height/2);
}

Vec2 VisibleRect::top()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width/2,
                sVisibleRect.origin.y+sVisibleRect.size.height);
}

Vec2 VisibleRect::bottom()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width/2,
                sVisibleRect.origin.y);
}

Vec2 VisibleRect::center()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width/2,
                sVisibleRect.origin.y+sVisibleRect.size.height/2);
}

Vec2 VisibleRect::leftTop()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x,
                sVisibleRect.origin.y+sVisibleRect.size.height);
}

Vec2 VisibleRect::rightTop()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width,
                sVisibleRect.origin.y+sVisibleRect.size.height);
}

Vec2 VisibleRect::leftBottom()
{
    lazyInit();
    return sVisibleRect.origin;
}

Vec2 VisibleRect::rightBottom()
{
    lazyInit();
    return Vec2(sVisibleRect.origin.x+sVisibleRect.size.width,
                sVisibleRect.origin.y);
}
