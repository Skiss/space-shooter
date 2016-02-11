#ifndef ENTITY_H
#define ENTITY_H

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Entity : public SceneNode
{
public:
    void setVelocity(const sf::Vector2f& v) { velocity_ = v; }
    void setVelocity(float x, float y) { velocity_.x = x; velocity_.y = y; }

    sf::Vector2f getVelocity() const { return velocity_; }

    void accelerate(const sf::Vector2f& vel);

    void setIsOutOfGameZone(bool val) { isOutOfGameZone_ = val; }
    bool isOutOfGameZone() const { return isOutOfGameZone_; }

    sf::FloatRect getBoundingBox() const override;

protected:
    void updateCurrent(const sf::Time& dt) override;

    sf::Sprite      sprite_;
    sf::Vector2f    velocity_;
    bool            isOutOfGameZone_ = false;
};

#endif