#include "EmiterNode.hpp"


EmiterNode::EmiterNode(Particle::Type type)
    : type_(type)
{

}

void EmiterNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
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
