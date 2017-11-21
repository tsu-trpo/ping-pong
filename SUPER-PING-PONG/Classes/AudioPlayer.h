#pragma once
#include "cocos2d.h"


class AudioPlayer
{
public:
    static constexpr char* HIT_PADDLE = "res/jump.wav";
    static constexpr char* HIT_BRICK = "res/hit.wav";
    static constexpr char* LOSE = "res/lose.wav";

    static constexpr char* BG = "res/bg_1.ogg";

    static void playBackgroundMusic();
    static void playEffect(const char* effect);
    static void stopAllEffects();
};