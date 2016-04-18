#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Data.hpp"
#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>

#include <cassert>


class CommandQueue;


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

    Projectile(Type type, const TextureHolder& textureHolder, CommandQueue& commandQueue, const sf::View& view);

    int getDamage() const { return data_.damage; }
    float getSpeed() const { return data_.speed; }

    const Aircraft* getMissileTarget() const
    {
        assert(type_ & Type::Missile);

        if (auto res = data_.target_.lock())
            return res.get();
        else
            return nullptr;
    }
    void setMissileTarget(const std::shared_ptr<Aircraft>& target)
    {
        assert(type_ & Type::Missile);
        data_.target_ = target;
    }

    bool isMissile() const { return (type_ & Type::Missile) > 0; }

    sf::FloatRect getBoundingBox() const override final;

private:
    void updateCurrent(const sf::Time& dt) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    unsigned getCategory() const override final;
    void destroyIfOutOfView();

    Type                    type_;
    Data::ProjectileData    data_;
    sf::Sprite              sprite_;
    CommandQueue&           commandQueue_;
    const sf::View&         view_;
};

#endif