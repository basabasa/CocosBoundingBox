#ifndef MoveComponent_hpp
#define MoveComponent_hpp

#include "cocos2d.h"

class MoveComponent : public cocos2d::Component
{
public:
    CREATE_FUNC(MoveComponent);
    
    void update(float delta) override;
    
    void setVelocity(cocos2d::Vec2 velocity);
    cocos2d::Vec2 getVelocity();
    
public:
    cocos2d::Vec2 mVelocity = cocos2d::Vec2::ZERO;
};

#endif /* MoveComponent_hpp */
