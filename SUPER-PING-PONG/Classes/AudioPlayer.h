#pragma once
#include "cocos2d.h"


class AudioPlayer
{
public:
    static constexpr const char* hitPaddle = "res/jump.wav";
    static constexpr const char* hitBrick = "res/hit.wav";
    static constexpr const char* lose = "res/lose.wav";

    static void playBackgroundMusic();
    static void playEffect(const char* effect);
    static void stopAllEffects();
};
