#pragma once
#include "cocos2d.h"


class AudioPlayer
{
public:
    static constexpr char* hitPaddle = (char*)"res/jump.wav";
    static constexpr char* hitBrick = (char*)"res/hit.wav";
    static constexpr char* lose = (char*)"res/lose.wav";

    static void playBackgroundMusic();
    static void playEffect(const char* effect);
    static void stopAllEffects();
};
