#include "AudioPlayer.h"
#include "SimpleAudioEngine.h"

const char *bgMusic = "res/bg_1.ogg";

CocosDenshion::SimpleAudioEngine &getPlayer()
{
    return *CocosDenshion::SimpleAudioEngine::getInstance();
}

void AudioPlayer::playBackgroundMusic()
{
    //getPlayer().playBackgroundMusic(bgMusic, true);
}

void AudioPlayer::playEffect(const char *effect)
{
    //getPlayer().playEffect(effect, false, 1.0f, 1.0f, 1.0f);
}

void AudioPlayer::stopAllEffects()
{
    getPlayer().stopAllEffects();
}