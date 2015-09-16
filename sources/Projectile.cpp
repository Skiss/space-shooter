#include "Projectile.hpp"

#include "ResourceHolder.hpp"


namespace
{
    std::vector<Projectile::Data> initAircraftData()
    {
        std::vector<Projectile::Data> data(Projectile::TypeCount);

        data[Projectile::Missile].damage = 200;
        data[Projectile::Missile].speed = 150.f;
        data[Projectile::Missile].textureID = TextureID::Missile;

        data[Projectile::Bullet].damage = 10;
        data[Projectile::Bullet].speed = 300.f;
        data[Projectile::Bullet].textureID = TextureID::Bullet;

        return data;
    }

    std::vector<Projectile::Data> data = initAircraftData();
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
