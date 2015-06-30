#ifndef ENTITY_H
#define ENTITY_H

#include "SceneNode.hpp"


class Entity : public SceneNode
{
public:
    void setVelocity(const sf::Vector2f& v) { velocity_ = v; }
    void setVelocity(float x, float y) { velocity_.x = x; velocity_.y = y; }

    sf::Vector2f getVelocity() const { return velocity_; }

private:
    void updateCurrent(const sf::Time& dt) override;

    sf::Vector2f velocity_;
};

#endif