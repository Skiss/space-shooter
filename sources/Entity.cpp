#include "Entity.hpp"


void Entity::updateCurrent(const sf::Time& dt)
{
    move(velocity_ * dt.asSeconds());
}