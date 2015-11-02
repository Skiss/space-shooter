#include "Aircraft.hpp"

#include "Category.hpp"
#include "ResourceHolder.hpp"
#include "TextNode.hpp"

#include <iostream>


namespace
{
    std::vector<Data::AircraftData> data = Data::initAircraftData();
}

Aircraft::Aircraft(Type type, CommandQueue& commandQueue, const TextureHolder& textureHolder, const FontHolder& fontHolder)
    : Entity()
    , type_(type)
    , data_(data[type_])
    , sprite_(textureHolder.get(data_.textureID))
    , commandQueue_(commandQueue)
{
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    auto textNode = std::make_unique<TextNode>("", fontHolder);
    healthText_ = textNode.get();
    healthText_->setPosition(0, -50.f);

    addChild(std::move(textNode));
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned Aircraft::getCategory() const
{
    return (type_ == Type::Eagle) ? Category::PlayerEntity : Category::EnemyAircraft;
}

void Aircraft::setIsFiring()
{
    isFiring_ = true;
}

void Aircraft::setIsLaunchingMissile()
{
    isLaunchingMissile_ = true;
}

void Aircraft::fire()
{
    std::cout << "Fire" << std::endl;
}

void Aircraft::launchMissile()
{
    std::cout << "Launch Missile" << std::endl;
}

void Aircraft::updateCurrent(const sf::Time& dt)
{
    updateMovements(dt);

    fireProjectiles(dt);

    Entity::updateCurrent(dt);
    healthText_->setText(std::to_string(data_.hp) + " HP");
    healthText_->setRotation(-getRotation());
}

void Aircraft::updateMovements(const sf::Time& dt)
{
    const auto& movements = data_.movements;

    if (movements.empty())
        return;

    // Checking if we need to change direction
    if (distanceTravelled_ >= movements.at(data_.movementsIndex).distance)
    {
        distanceTravelled_ = 0.f;
        data_.movementsIndex = (data_.movementsIndex + 1) % data_.movements.size();
    }

    const auto& move = data_.movements.at(data_.movementsIndex);
    sf::Vector2f vel(0, 1);

    if (move.angle == 45)
    {
        vel.y = 0.86602540378f;
        vel.x = 0.5f;
    }

    if (move.angle < 0)
        vel.x = -vel.x;

    vel.x *= data_.speed;
    vel.y *= data_.speed;

    setVelocity(vel);

    distanceTravelled_ += getSpeed() * dt.asSeconds();
}

void Aircraft::fireProjectiles(const sf::Time& dt)
{
    if (isFiring_ && fireCooldown_ <= sf::Time::Zero)
    {
        fire();
        isFiring_ = false;
        fireCooldown_ = sf::seconds(FIRE_RATE);
    }
    else
        fireCooldown_ -= dt;

    if (isLaunchingMissile_)
    {
        launchMissile();
        isLaunchingMissile_ = false;
    }
}
