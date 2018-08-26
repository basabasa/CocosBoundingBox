#include "MoveComponent.hpp"

USING_NS_CC;

void MoveComponent::update(float delta)
{
    Node* owner = this->getOwner();
    CCASSERT(owner != nullptr, "<!> owner is null.");

    owner->setPosition(owner->getPosition() + mVelocity * delta);
}

void MoveComponent::setVelocity(cocos2d::Vec2 velocity)
{
    mVelocity = velocity;
}

cocos2d::Vec2 MoveComponent::getVelocity()
{
    return mVelocity;
}
