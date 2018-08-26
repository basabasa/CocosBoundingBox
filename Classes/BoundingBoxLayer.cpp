#include "BoundingBoxLayer.hpp"
#include "MoveComponent.hpp"

USING_NS_CC;

void BoundingBoxLayer::onEnter()
{
    Layer::onEnter();
    
    this->initSubLayers();
    this->scheduleUpdate();
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

    MoveComponent* component = MoveComponent::create();
    component->setName("MoveComponent");
    component->setVelocity(Vec2(random(80, 140), random(80, 140)));
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
