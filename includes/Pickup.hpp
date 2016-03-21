#ifndef PICKUP_H
#define PICKUP_H

#include "Data.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>


class Pickup : public Entity
{
public:
    enum Type
    {
        FireRate,
        FireSpread,
        HealthRefill,
        MissileRefill,
        TypeCount
    };

    Pickup(Type type, const TextureHolder& textureHolder);

    unsigned getCategory() const override final;

    void applyEffect(Aircraft& a) const;

    sf::FloatRect getBoundingBox() const override final;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    Data::PickupData    data_;
    sf::Sprite          sprite_;
};

#endif