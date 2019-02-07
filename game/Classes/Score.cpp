#include "Score.h"
#include "Events.h"
#include "FilenameConstants.h"
#include "VisibleRect.h"

Score::Score()
{
    const int fontSize = 20;
    std::string scoreText = "Score: " + std::to_string(_score);
    _label = Label::createWithTTF(scoreText, file::font::score, fontSize);
    _label->setColor(Color3B::WHITE);
    _label->setAnchorPoint(Vec2(0, 1));

    Vec2 offset(10, -10);
    _label->setPosition(VisibleRect::leftTop() + offset);

    addChild(_label);
    addListeners();
};

Score::~Score()
{
    getEventDispatcher()->removeCustomEventListeners(event::hitBrick);
    getEventDispatcher()->removeCustomEventListeners(event::getbonus::scorePoints);
    getEventDispatcher()->removeCustomEventListeners(event::getbonus::scoreMultiplier);
    getEventDispatcher()->removeCustomEventListeners(event::loseBall);
}

void Score::updateLabel()
{
    _label->setString("Score: " + std::to_string(_score));
}

void Score::addListeners()
{
    auto hitBrickListener = EventListenerCustom::create(event::hitBrick, [=](EventCustom *event) {
        unsigned int hitPoints = 10;
        _score += hitPoints * _multiplier;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitBrickListener, 1);

    auto scorePointsListener = EventListenerCustom::create(event::getbonus::scorePoints, [=](EventCustom *event) {
        unsigned int bonusPoints = 150;
        _score += bonusPoints * _multiplier;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(scorePointsListener, 1);

    auto getScoreMultiplierListener =
        EventListenerCustom::create(event::getbonus::scoreMultiplier, [=](EventCustom *event) {
            _multiplier *= 2;
            updateLabel();
        });
    getEventDispatcher()->addEventListenerWithFixedPriority(getScoreMultiplierListener, 1);

    auto loseBallListener = EventListenerCustom::create(event::loseBall, [=](EventCustom *event) {
        _multiplier = 1;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);
}
