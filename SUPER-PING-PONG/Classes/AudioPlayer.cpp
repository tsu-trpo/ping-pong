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
        EventListenerCustom::create(event::hitBrick, [=](EventCustom *event) { playEffect(file::sound::hitBrick); });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitBrickListener, 1);

    auto hitPaddleListener =
        EventListenerCustom::create(event::hitPaddle, [=](EventCustom *event) { playEffect(file::sound::hitPaddle); });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitPaddleListener, 1);

    auto loseBallListener =
        EventListenerCustom::create(event::loseBall, [=](EventCustom *event) { playEffect(file::sound::loseBall); });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);
}

AudioPlayer::~AudioPlayer()
{
    getEventDispatcher()->removeCustomEventListeners(event::hitBrick);
    getEventDispatcher()->removeCustomEventListeners(event::hitPaddle);
    getEventDispatcher()->removeCustomEventListeners(event::loseBall);
}

void AudioPlayer::playEffect(const char *effect)
{
    getPlayer().playEffect(effect, false, 1.0f, 1.0f, 1.0f);
}

void AudioPlayer::playBackgroundMusic()
{
    getPlayer().playBackgroundMusic(file::music::background, true);
}

void AudioPlayer::stopAllEffects()
{
    getPlayer().stopAllEffects();
}
