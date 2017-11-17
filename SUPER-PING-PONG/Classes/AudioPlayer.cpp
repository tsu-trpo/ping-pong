#include "AudioPlayer.h"


void AudioPlayer::playBackgroundMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("res/bg_1.ogg", true);
}

void AudioPlayer::playEffect(const char* effect)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effect, false, 1.0f, 1.0f, 1.0f);
}

void AudioPlayer::stopAllEffects()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}


