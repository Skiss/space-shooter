#ifndef DATA_H
#define DATA_H

#include "ResourceIDs.hpp"

#include <SFML/System/Vector2.hpp>

#include <functional>
#include <vector>


class Aircraft;


namespace Data
{ 
    struct Movement
    {
        int     angle;
        float   distance;
    };

    struct AircraftData
    {
        int                     hp;
        float                   speed;
        TextureID               textureID;
        std::vector<Movement>   movements;
        unsigned                movementsIndex = 0;
    };

    struct ProjectileData
    {
        int             damage;
        float           speed;
        float           homingFactor;
        Aircraft*       target_;
        TextureID       textureID;
    };

    struct PickupData
    {
        TextureID                       textureID;
        std::function<void(Aircraft&)>  action;
    };

    std::vector<AircraftData> initAircraftData();
    std::vector<ProjectileData> initProjectileData();
    std::vector<PickupData> initPickupData();
}

#endif