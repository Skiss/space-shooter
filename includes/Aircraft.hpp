#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.hpp"

#include <SFML/Graphics.hpp>


class Aircraft : public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor
    };

    Aircraft(Type type, const sf::Texture& texture);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    unsigned getCategory() const override final;

private:
    Type        type_;
    sf::Sprite  sprite_;
};

#endif