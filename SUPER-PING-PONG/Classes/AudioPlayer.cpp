#include "AudioPlayer.h"
#include "Events.h"
#include "FilenameConstants.h"
#include "SimpleAudioEngine.h"

CocosDenshion::SimpleAudioEngine &getPlayer()
{
    return *CocosDenshion::SimpleAudioEngine::getInstance();
}

AudioPlayer::AudioPlayer()
{
    auto hitBrickListener =
        EventListenerCustom::create(hitBrick, [=](EventCustom *event) { playEffect(hitBrickEffect); });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitBrickListener, 1);

    auto hitPaddleListener =
        EventListenerCustom::create(hitPaddle, [=](EventCustom *event) { playEffect(hitPaddleEffect); });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitPaddleListener, 1);

    auto loseBallListener =
        EventListenerCustom::create(loseBall, [=](EventCustom *event) { playEffect(loseBallEffect); });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);
}

AudioPlayer::~AudioPlayer()
{
    getEventDispatcher()->removeCustomEventListeners(hitBrick);
    getEventDispatcher()->removeCustomEventListeners(hitPaddle);
    getEventDispatcher()->removeCustomEventListeners(loseBall);
}

void AudioPlayer::playEffect(const char *effect)
{
    getPlayer().playEffect(effect, false, 1.0f, 1.0f, 1.0f);
}

void AudioPlayer::playBackgroundMusic()
{
    getPlayer().playBackgroundMusic(backgroundMusic, true);
}

void AudioPlayer::stopAllEffects()
{
    getPlayer().stopAllEffects();
}
