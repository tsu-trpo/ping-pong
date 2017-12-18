#include "Life.h"
#include "VisibleRect.h"
#include "FilenameConstants.h"
#include "Events.h"


Life::Life()
{
    const int fontSize = 20;
    std::string scoreText = "Life: " + std::to_string(_life);
    _label = Label::createWithTTF(scoreText, file::font::score, fontSize);
    _label->setColor(Color3B::WHITE);
    _label->setAnchorPoint(Vec2(1, 1));

    Vec2 offset(-10, -10);
    _label->setPosition(VisibleRect::rightTop() + offset);

    addChild(_label);
    addListeners();
};

Life::~Life()
{
    getEventDispatcher()->removeCustomEventListeners(event::loseBall);
}

void Life::updateLabel()
{
    _label->setString("Life: " + std::to_string(_life));
}

void Life::addListeners()
{
    auto loseBallListener = EventListenerCustom::create(event::loseBall, [=](EventCustom *event) {

        _life -= 1;
        if(!_life)
        {
            getEventDispatcher()->dispatchCustomEvent(event::gameOver);
        }
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);


}
