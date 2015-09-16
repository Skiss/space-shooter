#include "Projectile.hpp"

#include "ResourceHolder.hpp"


namespace
{
    std::vector<Data::ProjectileData> data = Data::initProjectileData();
}

Projectile::Projectile(Type type, TextureHolder& textureHolder)
    : type_(type)
    , data_(data[type])
    , sprite_(textureHolder.get(data_.textureID))
{

}

void Projectile::updateCurrent(const sf::Time& dt)
{
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}
