#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    CREATE_FUNC(HelloWorld);

private:
    void initBoundingBoxLayers();
    void initMenuItems();
    
    void onTouchedAddItem();
    void onTouchedResetItem();
    
    cocos2d::Node* createBoundingObject();
};

#endif // __HELLOWORLD_SCENE_H__
