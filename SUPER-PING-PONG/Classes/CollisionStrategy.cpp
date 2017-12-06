#include "CollisionStrategy.h"
#include "AudioPlayer.h"

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
