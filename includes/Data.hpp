#ifndef DATA_H
#define DATA_H

#include "ResourceIDs.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <functional>
#include <memory>
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
        int                     maxHp;
        int                     hp;
        float                   speed;
        float                   fireRate;
        TextureID               textureID;
        sf::IntRect             textureRect;
        std::vector<Movement>   movements;
        unsigned                movementsIndex = 0;
    };

    struct ProjectileData
    {
        int                     damage;
        float                   speed;
        float                   homingFactor;
        std::weak_ptr<Aircraft> target_;
        TextureID               textureID;
        sf::IntRect             textureRect;
    };

    struct PickupData
    {
        TextureID                       textureID;
        sf::IntRect                     textureRect;
        std::function<void(Aircraft&)>  action;
    };

    std::vector<AircraftData> initAircraftData();
    std::vector<ProjectileData> initProjectileData();
    std::vector<PickupData> initPickupData();
}

#endif