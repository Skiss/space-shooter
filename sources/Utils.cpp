#include "Utils.hpp"

#include <cmath>


float utils::length(const sf::Vector2f& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f utils::normalize(const sf::Vector2f& v)
{
    return v / length(v);
}
