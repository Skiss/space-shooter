#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Data.hpp"
#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>

#include <cassert>


class Projectile : public Entity
{
public:
    enum Type
    {
        EnemyBullet = 1 << 0,
        AllyBullet = 1 << 1,
        Bullet = EnemyBullet | AllyBullet,
        AllyMissile = 1 << 2,
        EnemyMissile = 1 << 3,
        Missile = EnemyMissile | AllyMissile,
        TypeCount
    };

    Projectile(Type type, const TextureHolder& textureHolder);

    int getDamage() const { return data_.damage; }
    float getSpeed() const { return data_.speed; }

    const Aircraft* getMissileTarget() const
    {
        assert(type_ & Type::Missile);
        return data_.target_;
    }
    void setMissileTarget(Aircraft* target)
    {
        assert(type_ & Type::Missile);
        data_.target_ = target;
    }

    bool isMissile() const { return type_ == Type::Missile; }

private:
    void updateCurrent(const sf::Time& dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned getCategory() const override final;

    Type                    type_;
    Data::ProjectileData    data_;
};

#endif