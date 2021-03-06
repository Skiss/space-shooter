#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "Command.hpp"
#include "Data.hpp"
#include "Entity.hpp"
#include "Animation.hpp"
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

    Aircraft(Type type, CommandQueue& commandQueue, const TextureHolder& textureHolder, const FontHolder& fontHolder, const sf::View& view);
    ~Aircraft() = default;

    unsigned getCategory() const override final;

    unsigned getID() const { return id_; }
    float getSpeed() const { return data_.speed; }

    void setIsFiring();
    void setIsLaunchingMissile();
    void setEnemyList(std::vector<std::shared_ptr<Aircraft>>& list);

    void increaseFireRate() { data_.fireRate *= 2.f; }
    void repair(int healAmount);

    sf::FloatRect getBoundingBox() const override final;
    bool mustBeRemoved() const override;

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override final;
    void updateCurrent(const sf::Time& dt) override final;
    void updateMovements(const sf::Time& dt);

    void fireProjectiles(const sf::Time& dt);
    void createProjectile(SceneNode& node, const TextureHolder& textureHolder, Projectile::Type type);

    bool isPlayer() const { return type_ == Eagle; }

    static unsigned     idCpt_;
    unsigned            id_;

    Type                type_;
    Data::AircraftData  data_;
    sf::Sprite          sprite_;
    TextNode*           healthText_;
    Animation           explosion_;
    const sf::View&     view_;

    const std::vector<std::shared_ptr<Aircraft>>*   enemyList_ = nullptr;

    CommandQueue&       commandQueue_;
    Command             fireCommand_;
    Command             launchMissileCommand_;

    float               distanceTravelled_ = 0.f;
    bool                isFiring_ = false;
    bool                isLaunchingMissile_ = false;
    sf::Time            fireCooldown_ = sf::Time::Zero;
};

#endif
