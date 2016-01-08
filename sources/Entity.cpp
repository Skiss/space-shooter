#include "Entity.hpp"


void Entity::accelerate(const sf::Vector2f& vel)
{
    velocity_ += vel;
}

sf::FloatRect Entity::getBoundingBox() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Entity::updateCurrent(const sf::Time& dt)
{
    move(velocity_ * dt.asSeconds());
}