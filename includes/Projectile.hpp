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
        EnemyMissile,
        EnemyBullet,
        AllyBullet,
        TypeCount
    };

    Projectile(Type type, TextureHolder& textureHolder);

private:
    void updateCurrent(const sf::Time& dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned getCategory() const override final;
    int getDamage() const { return data_.damage; }
    float getSpeed() const { return data_.speed; }

    Type                    type_;
    Data::ProjectileData    data_;
    sf::Sprite              sprite_;
};

#endif