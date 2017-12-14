#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Score : public Node {
    unsigned int _score = 0;
    unsigned int _multiplier = 1;
    Label *_label = nullptr;

public:
    // Название события
    static constexpr const char *scoreEvent = "scoreEvent";

    // Параметры события хранящие количество очков
    // Событие scoreEvent принимает строку в которой хранится количество очков для зачисления
    static constexpr const char *hitBrick = "1";
    static constexpr const char *getBonus = "10";

    Score();
    ~Score();

    void addPoints(unsigned int points);
    void decPoints(unsigned int points);

    void setMultiplier(unsigned int newMultiplier);
    unsigned int getMultiplier() const;

private:
    void updateLabel();
    void addListener();
};
