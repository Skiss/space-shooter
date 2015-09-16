#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class Projectile : public Entity
{
public:
    enum Type
    {
        Missile,
        Bullet,
        TypeCount
    };

    struct Data
    {
        int         damage;
        float       speed;
        TextureID   textureID;
    };
    
    Projectile(Type type, TextureHolder& textureHolder);

private:
    virtual void updateCurrent(const sf::Time& dt) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    Type        type_;
    Data        data_;
    sf::Sprite  sprite_;
};

#endif