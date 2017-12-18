#pragma once
#include "cocos2d.h"

namespace tag
{
    const std::string ball = "ball";
    const std::string paddle = "paddle";
    const std::string brick = "brick";
    const std::string bottom = "bottom";
}


using namespace cocos2d;

inline bool isTagEqualTo(const PhysicsShape *shape, const std::string &tag)
{
    return shape->getBody()->getName() == tag;
}
