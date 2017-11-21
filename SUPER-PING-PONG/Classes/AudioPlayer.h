#pragma once
#include "cocos2d.h"


class AudioPlayer
{
public:
    static constexpr char* hitPaddle = "res/jump.wav";
    static constexpr char* hitBrick = "res/hit.wav";
    static constexpr char* lose = "res/lose.wav";

    static void playBackgroundMusic();
    static void playEffect(const char* effect);
    static void stopAllEffects();
};