#include "ContactHelper.h"
#include "ObjectTags.h"

ContactHelper::ContactHelper(PhysicsContact &contact, const std::string &mainTag)
{
    if (isTagEqualTo(contact.getShapeA(), mainTag)) {
        _main = contact.getShapeA();
        _other = contact.getShapeB();
    } else if (isTagEqualTo(contact.getShapeB(), mainTag)) {
        _main = contact.getShapeB();
        _other = contact.getShapeA();
    }
}

bool ContactHelper::wasContacted()
{
    return _main && _other;
}

PhysicsShape *ContactHelper::getOther()
{
    return _other;
}
