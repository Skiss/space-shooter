#include "EmiterNode.hpp"

#include "Command.hpp"
#include "CommandQueue.hpp"

EmiterNode::EmiterNode(Particle::Type type)
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

    }
}

void EmiterNode::emitParticles(float dt)
{
    particleNode_->addParticle(getWorldPosition());
}
