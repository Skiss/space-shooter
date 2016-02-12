#include "Entity.hpp"


void Entity::accelerate(const sf::Vector2f& vel)
{
    velocity_ += vel;
}

void Entity::damage(int dmgAmount)
{
    hp_ -= dmgAmount;
}

void Entity::destroy()
{
    hp_ = 0;
}

sf::FloatRect Entity::getBoundingBox() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Entity::updateCurrent(const sf::Time& dt)
{
    move(velocity_ * dt.asSeconds());
}

bool Entity::mustBeRemoved() const
{
    return isDestroyed();
}

bool Entity::isDestroyed() const
{
    return hp_ <= 0;
}
