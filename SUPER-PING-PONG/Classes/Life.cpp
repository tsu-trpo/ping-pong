#include "Life.h"
#include "Events.h"
#include "FilenameConstants.h"
#include "VisibleRect.h"

Life::Life()
{
    updateLabel();
    addListeners();
};

Life::~Life()
{
    getEventDispatcher()->removeCustomEventListeners(event::loseBall);
    getEventDispatcher()->removeCustomEventListeners(event::getbonus::lifePoints);
}

void Life::updateLabel()
{
    for (auto i : _bar) {
        i->removeFromParent();
    }
    _bar.clear();

    for (int i = 0; i < _life; i++) {
        auto heart = Sprite::create(file::texture::heart);
        Vec2 offset(-20 - 25 * i, -20);
        heart->setPosition(VisibleRect::rightTop() + offset);
        _bar.pushBack(heart);
        addChild(_bar.at(i));
    }
}

void Life::addListeners()
{
    auto loseBallListener = EventListenerCustom::create(event::loseBall, [=](EventCustom *event) {

        _life -= 1;
        if (!_life) {
            getEventDispatcher()->dispatchCustomEvent(event::gameOver);
        }
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(loseBallListener, 1);

    auto lifePointsListener = EventListenerCustom::create(event::getbonus::lifePoints, [=](EventCustom *event) {

        if (_life < 5) {
            _life += 1;
        } else {
            getEventDispatcher()->dispatchCustomEvent(event::getbonus::scorePoints);
            getEventDispatcher()->dispatchCustomEvent(event::getbonus::scoreMultiplier);
        }
        updateLabel();
    });
    getEventDispatcher()->addEventListenerWithFixedPriority(lifePointsListener, 1);
}
