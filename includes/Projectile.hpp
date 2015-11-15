#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Data.hpp"
#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class Projectile : public Entity
{
public:
    enum Type
    {
        EnemyBullet = 0,
        AllyBullet = 1 << 0,
        Bullet = EnemyBullet | AllyBullet,
        AllyMissile = 1 << 1,
        EnemyMissile = 1 << 2,
        Missile = EnemyMissile | AllyMissile,
        TypeCount
    };

    Projectile(Type type, const TextureHolder& textureHolder);

    int getDamage() const { return data_.damage; }
    float getSpeed() const { return data_.speed; }

private:
    void updateCurrent(const sf::Time& dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned getCategory() const override final;

    Type                    type_;
    Data::ProjectileData    data_;
    sf::Sprite              sprite_;
};

#endif