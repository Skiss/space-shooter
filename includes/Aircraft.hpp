#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Command.hpp"
#include "Data.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>


class CommandQueue;
class TextNode;

class Aircraft : public Entity
{
public:
    enum Type
    {
        Eagle,
        Raptor,
        Avenger,
        TypeCount
    };

    Aircraft(Type type, CommandQueue& commandQueue, const TextureHolder& textureHolder, const FontHolder& fontHolder);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;

    unsigned getCategory() const override final;

    int getHP() const { return data_.hp; }
    float getSpeed() const { return data_.speed; }

    void setIsFiring();
    void setIsLaunchingMissile();

private:
    void updateCurrent(const sf::Time& dt) override;
    void updateMovements(const sf::Time& dt);

    void fireProjectiles(const sf::Time& dt);
    void createBullet(SceneNode& node, const TextureHolder& textureHolder);

    bool isPlayer() const { return type_ == Eagle; }

    Type                type_;
    Data::AircraftData  data_;
    sf::Sprite          sprite_;
    TextNode*           healthText_;

    CommandQueue&       commandQueue_;
    Command             fireCommand_;
    Command             launchMissileCommand_;

    float               distanceTravelled_ = 0.f;
    bool                isFiring_ = false;
    bool                isLaunchingMissile_ = false;
    sf::Time            fireCooldown_ = sf::Time::Zero;
    const float         FIRE_RATE = 2.f;
};

#endif
