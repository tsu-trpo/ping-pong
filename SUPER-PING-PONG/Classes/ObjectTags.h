#pragma once

const std::string ballTag = "ball";
const std::string paddleTag = "paddle";
const std::string brickTag = "brick";

inline bool isTagEqualTo(const PhysicsShape *shape, const std::string &tag)
{
    return shape->getBody()->getName() == tag;
}
