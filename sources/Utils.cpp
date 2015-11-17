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

float utils::dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float utils::toDegree(float radian)
{
    return 180.f / PI * radian;
}
