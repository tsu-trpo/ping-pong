#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class ContactHelper {
    PhysicsShape *_main = nullptr;
    PhysicsShape *_other = nullptr;

public:
    ContactHelper(PhysicsContact &contact, const std::string &mainTag);

    bool wasContacted();

    PhysicsShape *getOther();
    PhysicsShape *getMain();

};
