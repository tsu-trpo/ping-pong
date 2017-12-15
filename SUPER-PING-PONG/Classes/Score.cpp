#include "Score.h"
#include "Events.h"
#include "FilenameConstants.h"
#include "VisibleRect.h"

Score::Score()
{
    const int fontSize = 20;
    std::string scoreText = "Score: " + std::to_string(_score * 10);
    _label = Label::createWithTTF(scoreText, scoreFont, fontSize);
    _label->setColor(Color3B::WHITE);
    _label->setAnchorPoint(Vec2(0, 1));

    Vec2 offset(10, -10);
    _label->setPosition(VisibleRect::leftTop() + offset);

    addChild(_label);
    addListeners();
};

Score::~Score()
{
    getEventDispatcher()->removeCustomEventListeners(hitBrick);
    getEventDispatcher()->removeCustomEventListeners(getScoreBonus);
    getEventDispatcher()->removeCustomEventListeners(getScoreMultiplier);
    getEventDispatcher()->removeCustomEventListeners(loseBall);
}

void Score::updateLabel()
{
    _label->setString("Score: " + std::to_string(_score * 10));
}

void Score::addListeners()
{
    auto hitBrickListener = EventListenerCustom::create(hitBrick, [=](EventCustom *event) {
        _score += _multiplier;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(hitBrickListener, 1);

    auto getScoreBonusListener = EventListenerCustom::create(getScoreBonus, [=](EventCustom *event) {
        unsigned int bonusPoints = 10;
        _score += bonusPoints * _multiplier;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(getScoreBonusListener, 1);

    auto getScoreMultiplierListener = EventListenerCustom::create(getScoreMultiplier, [=](EventCustom *event) {
        _multiplier *= 2;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(getScoreMultiplierListener, 1);

    auto loseBallListener = EventListenerCustom::create(loseBall, [=](EventCustom *event) {
        _multiplier = 1;
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);
}
