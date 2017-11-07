#include "CollisionStrategy.h"


bool Classic::collideWithBrick(Ball* ball, Brick *brick)
{
    auto brickRect = brick->getRect();
    brickRect.origin.x += brick->getPosition().x;
    brickRect.origin.y += brick->getPosition().y;

    if (ball->getBoundingBox().intersectsRect(brickRect))
    {
        auto ballRect = ball->getBoundingBox();

        if ((ballRect.getMinY() < brickRect.getMaxY() && ballRect.getMinY() > brickRect.getMinY()) ||
                (ballRect.getMaxY() > brickRect.getMinY() && ballRect.getMaxY() < brickRect.getMaxY()))
        {
            Vec2 ballDirection = ball->getDirection();
            if (ballRect.getMinX() < brickRect.getMaxX() && ballRect.getMaxX() > brickRect.getMaxX())
            {
                // right
                //setPosition(brickRect.getMaxX() + radius(),getPosition().y);
                ball->setDirection( Vec2( fabsf(ballDirection.x), ballDirection.y));
            } else if (ballRect.getMaxX() > brickRect.getMinX() && ballRect.getMinX() < brickRect.getMinX())
            {
                // left
                //setPosition(brickRect.getMinX() - radius(),getPosition().y);
                ball->setDirection( Vec2( -fabsf(ballDirection.x), ballDirection.y));
            }

            if (ballRect.getMinY() < brickRect.getMaxY() && ballRect.getMinY() > brickRect.getMinY())
            {
                // top
                //setPosition(getPosition().x, brickRect.getMaxY() + radius());
                ball->setDirection( Vec2( ballDirection.x, fabsf(ballDirection.y)));
            } else
            {
                //bottom
                //setPosition(getPosition().x, brickRect.getMinY() - radius());
                ball->setDirection( Vec2( ballDirection.x, -fabsf(ballDirection.y)));

            }
        }
        return true;
    }
    return false;
}


bool Sharp::collideWithBrick(Ball* ball, Brick *brick)
{
    auto brickRect = brick->getRect();
    brickRect.origin.x += brick->getPosition().x;
    brickRect.origin.y += brick->getPosition().y;

    if (ball->getBoundingBox().intersectsRect(brickRect))
    {
        return true;
    }
    return false;
}
