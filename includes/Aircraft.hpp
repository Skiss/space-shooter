#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class Aircraft : public Entity
{
public:
    enum Type
    {
        Eagle,
        Raptor,
        TypeCount
    };

    struct Data
    {
        int         hp;
        float       speed;
        TextureID   textureID;
    };

    Aircraft(Type type, const TextureHolder& textureHolder);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    unsigned getCategory() const override final;

    int getHP() const { return data_.hp; }
    float getspeed() const { return data_.speed; }

private:
    Type            type_;
    Data            data_;
    sf::Sprite      sprite_;
};

#endif