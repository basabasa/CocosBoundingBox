#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BoundingBoxLayer.hpp"

USING_NS_CC;

enum UI_TAG {
    UI_TAG_BOX_LAYER = 1,
};

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    this->initBoundingBoxLayers();
    this->initMenuItems();

    return true;
}

void HelloWorld::initBoundingBoxLayers()
{
    const Size size = this->getContentSize();
    const Size boundingSize = size * 0.7f;
    const Vec2 boundingPos  = (size - boundingSize) / 2;
    
    LayerColor* wall = LayerColor::create(Color4B::WHITE);
    wall->setContentSize(boundingSize + Size(4.f, 4.f));
    wall->setPosition(boundingPos - Vec2(2.f, 2.f));
    this->addChild(wall);
    
    LayerColor* boxBg = LayerColor::create(Color4B::BLACK);
    boxBg->setContentSize(boundingSize);
    boxBg->setPosition(boundingPos);
    this->addChild(boxBg);
    
    BoundingBoxLayer* boxLayer = BoundingBoxLayer::create();
    boxLayer->setTag(UI_TAG_BOX_LAYER);
    boxLayer->setContentSize(boundingSize);
    boxLayer->setPosition(boundingPos);
    this->addChild(boxLayer);
}

void HelloWorld::initMenuItems()
{
    Vector<MenuItem*> menuItems;
    
    {
        Label *label = Label::createWithSystemFont("add", "Arial", 26);
        MenuItemLabel *item = MenuItemLabel::create(label, std::bind(&HelloWorld::onTouchedAddItem, this));
        menuItems.pushBack(item);
    }
    {
        Label *label = Label::createWithSystemFont("reset", "Arial", 26);
        MenuItemLabel *item = MenuItemLabel::create(label, std::bind(&HelloWorld::onTouchedResetItem, this));
        menuItems.pushBack(item);
    }

    Menu *menu = Menu::createWithArray(menuItems);
    menu->alignItemsHorizontallyWithPadding(50.f);
    menu->setPositionY(this->getContentSize().height * 0.1f);
    this->addChild(menu);
}

void HelloWorld::onTouchedAddItem()
{
    BoundingBoxLayer* boxLayer = this->getChildByTag<BoundingBoxLayer*>(UI_TAG_BOX_LAYER);
    CCASSERT(boxLayer != nullptr, "<!> BoundingBoxLayer is null.");
    
    Node* object = this->createBoundingObject();
    boxLayer->addBoundingObject(object);
}

void HelloWorld::onTouchedResetItem()
{
    BoundingBoxLayer* boxLayer = this->getChildByTag<BoundingBoxLayer*>(UI_TAG_BOX_LAYER);
    CCASSERT(boxLayer != nullptr, "<!> BoundingBoxLayer is null.");

    boxLayer->resetBoundingObject();
}

cocos2d::Node* HelloWorld::createBoundingObject()
{
    LayerColor *object = LayerColor::create(Color4B::GRAY, 40, 40);
    
    Color4B colors[5] = {
        Color4B::RED,
        Color4B::BLUE,
        Color4B::GREEN,
        Color4B::YELLOW,
        Color4B::MAGENTA,
    };
    int index = random(0, 4);
    
    LayerColor *objectContent = LayerColor::create(colors[index], 38, 38);
    objectContent->setPosition(1, 1);
    object->addChild(objectContent);

    return object;
}
