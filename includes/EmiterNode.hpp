#ifndef EMITERNODE_H
#define EMITERNODE_H

#include "ParticleNode.hpp"
#include "SceneNode.hpp"


class EmiterNode : public SceneNode
{
public:
    explicit EmiterNode(Particle::Type type);

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateCurrent(const sf::Time& dt) override;

    void emitParticles(float dt);

    Particle::Type  type_;
    sf::Time        accTime_;
    ParticleNode*   particleNode_ = nullptr;
};

#endif