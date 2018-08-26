#include "BoundingBoxLayer.hpp"
#include "MoveComponent.hpp"

USING_NS_CC;

void BoundingBoxLayer::onEnter()
{
    Layer::onEnter();
    
    this->initSubLayers();
    this->scheduleUpdate();
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void BoundingBoxLayer::onExit()
{
    Layer::onExit();
    
    this->unscheduleUpdate();
}

void BoundingBoxLayer::update(float delta)
{
    for (Node* child : this->getChildren())
    {
        MoveComponent* move = dynamic_cast<MoveComponent*>(child->getComponent("MoveComponent"));
        if (move == nullptr)
        {
            continue;
        }
        
        Vec2 pos = child->getPosition();
        
        if (pos.x < 0 || pos.x >= this->getContentSize().width - child->getContentSize().width)
        {
            Vec2 velocity = move->getVelocity();
            child->setPosition(child->getPosition() - velocity * delta);
            
            velocity.x *= -1.f;
            move->setVelocity(velocity);
        }
        if (pos.y < 0 || pos.y >= this->getContentSize().height - child->getContentSize().height)
        {
            Vec2 velocity = move->getVelocity();
            child->setPosition(child->getPosition() - velocity * delta);
            
            velocity.y *= -1.f;
            move->setVelocity(velocity);
        }
    }
}

void BoundingBoxLayer::addBoundingObject(cocos2d::Node* object)
{
    object->setPosition((this->getContentSize() - object->getContentSize()) / 2);
    
    const float angle = random(0, 359);
    const float angleRad = angle * (M_PI / 180.f);
    Vec2 velocity = Vec2(cos(angleRad), sin(angleRad));
    velocity *= random(70, 140);

    MoveComponent* component = MoveComponent::create();
    component->setName("MoveComponent");
    component->setVelocity(velocity);
    object->addComponent(component);
    
    this->addChild(object);
}

void BoundingBoxLayer::resetBoundingObject()
{
    std::vector<Node*> boundingObjects = {};
    
    for (Node* child : this->getChildren())
    {
        MoveComponent* move = dynamic_cast<MoveComponent*>(child->getComponent("MoveComponent"));
        if (move == nullptr)
        {
            continue;
        }
        
        boundingObjects.push_back(child);
    }
    
    for (Node* object : boundingObjects)
    {
        object->removeFromParent();
    }
}

void BoundingBoxLayer::initSubLayers()
{
    ParticleSystemQuad* emitter = ParticleSystemQuad::create("particle/centralPart.plist");
    emitter->setPosition(this->getContentSize() / 2);
    this->addChild(emitter);
}

bool BoundingBoxLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void BoundingBoxLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    const Vec2 touchLocation = this->convertTouchToNodeSpace(touch);
    std::vector<Node*> touchedNodes = {};
    
    for (Node* child : this->getChildren())
    {
        MoveComponent* move = dynamic_cast<MoveComponent*>(child->getComponent("MoveComponent"));
        if (move == nullptr)
        {
            continue;
        }
        
        Rect childArea = Rect(child->getPosition(), child->getContentSize());
        
        const bool isTouched = childArea.containsPoint(touchLocation);
        if (!isTouched)
        {
            continue;
        }
        
        touchedNodes.push_back(child);
    }
    
    for (Node* node : touchedNodes)
    {
        node->removeFromParent();
    }
}
