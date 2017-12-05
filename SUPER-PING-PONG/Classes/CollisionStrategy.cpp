#include "CollisionStrategy.h"
#include "AudioPlayer.h"

bool Classic::collideWithBrick(Ball &ball, Brick &brick)
{
/*    auto brickBox = brick.getBox();

    if (ball.getBoundingBox().intersectsRect(brickBox))
    {
        auto ballRect = ball.getBoundingBox();

        if ((ballRect.getMinY() < brickBox.getMaxY() && ballRect.getMinY() > brickBox.getMinY()) ||
                (ballRect.getMaxY() > brickBox.getMinY() && ballRect.getMaxY() < brickBox.getMaxY()))
        {
            Vec2 ballDirection = ball.getDirection();
            if (ballRect.getMinX() < brickBox.getMaxX() && ballRect.getMaxX() > brickBox.getMaxX())
            {
                // right
                ball.setDirection( Vec2( fabsf(ballDirection.x), ballDirection.y));
            } else if (ballRect.getMaxX() > brickBox.getMinX() && ballRect.getMinX() < brickBox.getMinX())
            {
                // left
                ball.setDirection( Vec2( -fabsf(ballDirection.x), ballDirection.y));
            }

            if (ballRect.getMinY() < brickBox.getMaxY() && ballRect.getMinY() > brickBox.getMinY())
            {
                // top
                ball.setDirection( Vec2( ballDirection.x, fabsf(ballDirection.y)));
            } else
            {
                //bottom
                ball.setDirection( Vec2( ballDirection.x, -fabsf(ballDirection.y)));
            }
        }
        AudioPlayer::playEffect(AudioPlayer::hitBrick);       
        return true;
    }
    return false;*/
}


bool Sharp::collideWithBrick(Ball &ball, Brick &brick)
{
    auto brickBox = brick.getBox();

    if (ball.getBoundingBox().intersectsRect(brickBox))
    {
        AudioPlayer::playEffect(AudioPlayer::hitBrick);
        return true;
    }
    return false;
}
