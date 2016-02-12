#ifndef ENTITY_H
#define ENTITY_H

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Entity : public SceneNode
{
public:
    Entity(int hp)
        : hp_(hp)
    {}

    void setVelocity(const sf::Vector2f& v) { velocity_ = v; }
    void setVelocity(float x, float y) { velocity_.x = x; velocity_.y = y; }

    sf::Vector2f getVelocity() const { return velocity_; }
    int getHP() const { return hp_; }

    void accelerate(const sf::Vector2f& vel);
    void damage(int dmgAmount);
    void destroy();

    bool mustBeRemoved() const override;
    virtual bool isDestroyed() const;

    void setIsOutOfGameZone(bool val) { isOutOfGameZone_ = val; }
    bool isOutOfGameZone() const { return isOutOfGameZone_; }

    sf::FloatRect getBoundingBox() const override;

protected:
    void updateCurrent(const sf::Time& dt) override;

    sf::Sprite      sprite_;
    sf::Vector2f    velocity_;
    int             hp_;
    bool            isOutOfGameZone_ = false;
};

#endif