#pragma once
#include "cocos2d.h"

using namespace cocos2d;

const std::string ballTag = "ball";
const std::string paddleTag = "paddle";
const std::string brickTag = "brick";
const std::string bonusTag = "bonus";

inline bool isTagEqualTo(const PhysicsShape *shape, const std::string &tag)
{
    return shape->getBody()->getName() == tag;
}
