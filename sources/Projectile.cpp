#include "Projectile.hpp"


Projectile::Projectile(Type type, TextureHolder& textureHolder)
    : type_(type)
{

}

void Projectile::updateCurrent(const sf::Time& dt)
{
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
}
