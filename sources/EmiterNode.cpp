#include "EmiterNode.hpp"


EmiterNode::EmiterNode(Particle::Type type)
    : type_(type)
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

}
