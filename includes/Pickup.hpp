#ifndef PICKUP_H
#define PICKUP_H

#include "Data.hpp"
#include "Entity.hpp"


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

private:
    Data::PickupData    data_;
};

#endif