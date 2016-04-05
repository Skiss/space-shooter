#include "ParticleNode.hpp"

#include "Data.hpp"
#include "ResourceHolder.hpp"


namespace
{
    std::vector<Data::ParticleData> data = Data::initParticleData();
}


ParticleNode::ParticleNode(Particle::Type type, const TextureHolder& textureHolder)
    : type_(type)
    , texture_(textureHolder.get(TextureID::Particle))
    , vertewArray_(sf::Quads)
    , needUpdate_(true)
{
}

void ParticleNode::addParticle(const sf::Vector2f& pos)
{
    particles_.emplace_back(pos, data[type_].color_, data[type_].lifeTime_);
}

void ParticleNode::updateCurrent(const sf::Time & dt)
{
}

void ParticleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
}
