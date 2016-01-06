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

    void applyEffect(Aircraft& a) const;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    Data::PickupData    data_;
};

#endif