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
    // Removing out of date particles
    while (!particles_.empty() && particles_.front().remainingTime < sf::Time::Zero)
        particles_.pop_front();

    // Updating the remaining particles
    for (auto& p : particles_)
        p.remainingTime -= dt;

    needUpdate_ = true;
}

void ParticleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    if (needUpdate_)
    {
        computeVertices();
        needUpdate_ = false;
    }

    states.texture = &texture_;
    target.draw(vertewArray_, states);
}

void ParticleNode::computeVertices() const
{
    sf::Vector2f size(texture_.getSize());
    sf::Vector2f half = size / 2.f;

    vertewArray_.clear();

    for (const auto& p : particles_)
    {
        auto pos = p.pos;
        auto color = p.color;

        float visibility = p.remainingTime.asSeconds() / data[type_].lifeTime_.asSeconds();
        color.a = static_cast<sf::Uint8>(255.f * std::max(visibility, 0.f));

        addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
        addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
        addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
        addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);
    }
}

void ParticleNode::addVertex(float x, float y, float textX, float textY, const sf::Color& c) const
{
    sf::Vertex v;

    v.position = { x, y };
    v.texCoords = { textX, textY };
    v.color = c;

    vertewArray_.append(v);
}
