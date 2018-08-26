#ifndef BoundingBoxLayer_hpp
#define BoundingBoxLayer_hpp

#include "cocos2d.h"

class BoundingBoxLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(BoundingBoxLayer);
    
    void onEnter() override;
    void onExit() override;
    void update(float delta) override;
    
    void addBoundingObject(cocos2d::Node* object);
    void resetBoundingObject();
    
private:
    void initSubLayers();
};

#endif /* BoundingBoxLayer_hpp */
