#include "Entity.hpp"


void Entity::accelerate(const sf::Vector2f& vel)
{
    velocity_ += vel;
}

void Entity::updateCurrent(const sf::Time& dt)
{
    move(velocity_ * dt.asSeconds());
}