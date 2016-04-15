#include "EmiterNode.hpp"

#include "Command.hpp"
#include "CommandQueue.hpp"

#include <cassert>


namespace
{
    template <typename TargetType>
    std::function<void(SceneNode*, const sf::Time& dt)> createAction(std::function<void(ParticleNode& a)> func)
    {
        return [=](SceneNode* node, const sf::Time&)
        {
            assert(dynamic_cast<TargetType*>(node));

            func(static_cast<TargetType&>(*node));
        };
    }
}

EmiterNode::EmiterNode(Particle::Type type, CommandQueue& commandQueue)
    : type_(type)
    , commandQueue_(commandQueue)
{

}

void EmiterNode::updateCurrent(const sf::Time& dt)
{
    if (particleNode_)
        emitParticles(dt.asSeconds());
    else
    {
        auto findParticleNode = createAction<ParticleNode>([this] (ParticleNode& node)
        {
            if (node.getType() == type_)
                particleNode_ = &node;
        });

        Command c;
        c.category_ = Category::ParticleSystem;
        c.action_ = findParticleNode;
        
        commandQueue_.push(c);
    }
}

void EmiterNode::emitParticles(float dt)
{
    particleNode_->addParticle(getWorldPosition());
}
