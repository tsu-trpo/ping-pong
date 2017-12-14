#include "Score.h"
#include "VisibleRect.h"

Score::Score()
{
    const int fontSize = 20;
    std::string scoreText = "Score: " + std::to_string(_score * 10);
    _label = Label::createWithTTF(scoreText, "fonts/FFFFORWA.TTF", fontSize);
    _label->setColor(Color3B::WHITE);
    _label->setAnchorPoint(Vec2(0, 1));

    Vec2 offset(10, -10);
    _label->setPosition(VisibleRect::leftTop() + offset);

    addChild(_label);
    addListener();
};

Score::~Score()
{
    getEventDispatcher()->removeCustomEventListeners(scoreEvent);
}

void Score::addPoints(unsigned int points)
{
    _score += points * _multiplier;
    updateLabel();
}

void Score::decPoints(unsigned int points)
{
    _score -= points;
    updateLabel();
}

void Score::setMultiplier(unsigned int newMultiplier)
{
    _multiplier = newMultiplier;
}

unsigned int Score::getMultiplier() const
{
    return _multiplier;
}

void Score::updateLabel()
{
    _label->setString("Score: " + std::to_string(_score * 10));
}

void Score::addListener()
{
    auto _hitListener = EventListenerCustom::create(scoreEvent, [=](EventCustom *event) {

        // convert char* to int
        int points = atoi((char *) event->getUserData());

        _score += points * _multiplier;
        updateLabel();
    });

    getEventDispatcher()->addEventListenerWithFixedPriority(_hitListener, 1);
}
