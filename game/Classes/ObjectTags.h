#pragma once
#include "cocos2d.h"

using namespace cocos2d;

namespace tag {

const std::string ball = "ball";
const std::string paddle = "paddle";
const std::string brick = "brick";
const std::string bottom = "bottom";
const std::string bonus = "bonus";
}  // namespace tag

inline bool isTagEqualTo(const PhysicsShape *shape, const std::string &tag)
{
    return shape->getBody()->getName() == tag;
}
