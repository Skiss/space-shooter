#include "Projectile.hpp"

#include "Category.hpp"
#include "ResourceHolder.hpp"


namespace
{
    std::vector<Data::ProjectileData> data = Data::initProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textureHolder)
    : type_(type)
    , data_(data[type])
    , sprite_(textureHolder.get(data_.textureID))
{
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Projectile::updateCurrent(const sf::Time& dt)
{
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned Projectile::getCategory() const
{
    if (type_ == AllyBullet)
        return Category::AllyProjectile;
    else
        return Category::EnemyProjectile;
}
