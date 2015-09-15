#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class Projectile : public Entity
{
public:
    enum class Type
    {
        Missile,
        Bullet
    };

    Projectile(Type type, TextureHolder& textureHolder);

private:
    virtual void updateCurrent(const sf::Time& dt) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    Type        type_;
    sf::Sprite  sprite_;
};

#endif