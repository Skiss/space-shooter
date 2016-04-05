#ifndef PARTICLE_H
#define PARTICLE_H

#include "ResourceIDs.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics.hpp>

#include <deque>


struct Particle
{
    enum Type
    {
        Smoke,
        Trail,
        Count
    };

    Particle(sf::Vector2f pos, sf::Color color, sf::Time lifeTime)
        : pos(pos)
        , color(color)
        , lifeTime(lifeTime)
    {}

    sf::Vector2f    pos;
    sf::Color       color;
    sf::Time        lifeTime;
};

class ParticleNode : public SceneNode
{
public:
    explicit ParticleNode(Particle::Type type, const TextureHolder& textureHolder);
    virtual ~ParticleNode() = default;

    void addParticle(const sf::Vector2f& pos);
    
    Particle::Type getType() const { return type_; }
    unsigned getCategory() const override { return Category::ParticleSystem; }

private:
    void updateCurrent(const sf::Time& dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::deque<Particle>    particles_;
    Particle::Type          type_;
    const sf::Texture&      texture_;

    mutable sf::VertexArray vertewArray_;
    mutable bool            needUpdate_;
};

#endif