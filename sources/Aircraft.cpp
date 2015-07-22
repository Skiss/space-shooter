#include "Aircraft.hpp"

#include "Category.hpp"


Aircraft::Aircraft(Type type, const sf::Texture& texture)
    : Entity()
    , type_(type)
    , sprite_(texture)
{
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned Aircraft::getCategory() const
{
    return (type_ == Type::Eagle) ? Category::PlayerEntity : Category::EnemyEntity;
}
