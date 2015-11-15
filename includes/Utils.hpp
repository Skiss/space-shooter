#ifndef WORLD_H
#define WORLD_H

#include <SFML/System/Vector2.hpp>


namespace utils
{
    float length(const sf::Vector2f& v);
    sf::Vector2f normalize(const sf::Vector2f& v);
}

#endif
