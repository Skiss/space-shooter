#ifndef DATA_H
#define DATA_H

#include "ResourceIDs.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>


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
        sf::Vector2f    targetPos_;
        TextureID       textureID;
    };

    std::vector<AircraftData> initAircraftData();
    std::vector<ProjectileData> initProjectileData();
}

#endif