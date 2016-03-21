#include "Pickup.hpp"

#include "ResourceHolder.hpp"


namespace
{
    std::vector<Data::PickupData> data = Data::initPickupData();
}


Pickup::Pickup(Type type, const TextureHolder& textureHolder)
    : Entity(1)
    , data_(data[type])
    , sprite_(textureHolder.get(data_.textureID), data_.textureRect)
{ }

unsigned Pickup::getCategory() const
{
    return Category::PickUp;
}

void Pickup::applyEffect(Aircraft& a) const
{
    data_.action(a);
}

sf::FloatRect Pickup::getBoundingBox() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
