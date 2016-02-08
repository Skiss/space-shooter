#include "Pickup.hpp"

#include "ResourceHolder.hpp"


namespace
{
    std::vector<Data::PickupData> data = Data::initPickupData();
}


Pickup::Pickup(Type type, const TextureHolder& textureHolder)
    : data_(data[type])
{
    Entity::sprite_.setTexture(textureHolder.get(data_.textureID));
}

unsigned Pickup::getCategory() const
{
    return Category::PickUp;
}

void Pickup::applyEffect(Aircraft& a) const
{
    data_.action(a);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
