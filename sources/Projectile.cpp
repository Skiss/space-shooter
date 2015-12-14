#include "Projectile.hpp"

#include "Aircraft.hpp"
#include "Category.hpp"
#include "ResourceHolder.hpp"
#include "Utils.hpp"


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

    setVelocity(sf::Vector2f(0.f, -1.f));
}

void Projectile::updateCurrent(const sf::Time& dt)
{
    // Handle missile auto-guidance
    if (type_ & Projectile::Missile)
    {
        sf::Vector2f newVelocity = (data_.target_ && !data_.target_->isDestroyed())
                                    ? utils::normalize(data_.target_->getPosition() - getPosition())
                                    : utils::normalize(velocity_);

        newVelocity = utils::normalize(newVelocity + (velocity_ * data_.homingFactor));
        newVelocity *= data_.speed;
        velocity_ = newVelocity;

        float angle = std::atan2f(velocity_.y, velocity_.x);
        setRotation(utils::toDegree(angle) + 90.f);
    }

    Entity::updateCurrent(dt);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned Projectile::getCategory() const
{
    if (type_ == AllyBullet || type_ == AllyMissile)
        return Category::AllyProjectile;
    else
        return Category::EnemyProjectile;
}
