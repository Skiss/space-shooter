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

    Aircraft(Type type, const sf::Texture& texture, const sf::Vector2f& velocity);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Type        type_;
    sf::Sprite  sprite_;
};

#endif