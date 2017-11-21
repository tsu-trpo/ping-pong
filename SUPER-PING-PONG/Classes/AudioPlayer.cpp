#include "AudioPlayer.h"
#include "SimpleAudioEngine.h"

CocosDenshion::SimpleAudioEngine &getPlayer()
{
    return *CocosDenshion::SimpleAudioEngine::getInstance();
}

void AudioPlayer::playBackgroundMusic()
{
    getPlayer().playBackgroundMusic("res/bg_1.ogg", true);
}

void AudioPlayer::playEffect(const char* effect)
{
    getPlayer().playEffect(effect, false, 1.0f, 1.0f, 1.0f);
}

void AudioPlayer::stopAllEffects()
{
    getPlayer().stopAllEffects();
}