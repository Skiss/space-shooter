#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Entity.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class TextNode;

class Aircraft : public Entity
{
public:
    enum Type
    {
        Eagle,
        Raptor,
        TypeCount
    };

    struct Movement
    {
        int         angle;
        unsigned    distance;
    };

    struct Data
    {
        int                     hp;
        float                   speed;
        TextureID               textureID;
        std::vector<Movement>   movements;
        unsigned                movementsIndex = 0;
    };

    Aircraft(Type type, const TextureHolder& textureHolder, const FontHolder& fontHolder);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    unsigned getCategory() const override final;

    int getHP() const { return data_.hp; }
    float getSpeed() const { return data_.speed; }

private:
    void updateCurrent(const sf::Time& dt) override;
    void updateMovements(const sf::Time& dt);

    Type            type_;
    Data            data_;
    sf::Sprite      sprite_;
    TextNode*       healthText_;
    unsigned        distanceTravelled_ = 0;
};

#endif
