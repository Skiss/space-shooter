#ifndef EMITERNODE_H
#define EMITERNODE_H

#include "ParticleNode.hpp"
#include "SceneNode.hpp"


class CommandQueue;

class EmiterNode : public SceneNode
{
public:
    explicit EmiterNode(Particle::Type type, CommandQueue& commandQueue);

private:
    void updateCurrent(const sf::Time& dt) override;

    void emitParticles(float dt);

    Particle::Type  type_;
    sf::Time        accTime_;
    ParticleNode*   particleNode_ = nullptr;
    CommandQueue&   commandQueue_;
};

#endif