#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class AudioPlayer : public Node {
public:
    AudioPlayer();
    ~AudioPlayer();

    static void playBackgroundMusic();
    static void stopAllEffects();

private:
    void playEffect(const char *effect);
};
