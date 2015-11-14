#include "Aircraft.hpp"

#include "Category.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TextNode.hpp"


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

    // Init shoot commands
    fireCommand_.category_ = Category::SceneAirLayer;
    fireCommand_.action_ = [this, &textureHolder] (SceneNode* node, const sf::Time& dt)
    {
        createBullet(*node, textureHolder);
    };

    launchMissileCommand_.category_ = Category::SceneAirLayer;
    launchMissileCommand_.action_ = [] (SceneNode*, const sf::Time& dt)
    {

    };


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

void Aircraft::createBullet(SceneNode& node, const TextureHolder& textureHolder)
{
    Projectile::Type bulletType = (isPlayer()) ? Projectile::AllyBullet : Projectile::EnemyBullet;
    int bulletDirection = (isPlayer()) ? -1 : 1;

    std::unique_ptr<Projectile> bullet(new Projectile(bulletType, textureHolder));

    bullet->setPosition(this->getPosition());
    bullet->setVelocity({0, bullet->getSpeed() * bulletDirection});

    node.addChild(std::move(bullet));
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
    if (isFiring_ && fireCooldown_ < sf::Time::Zero)
    {
        commandQueue_.push(&fireCommand_);
        fireCooldown_ = sf::seconds(FIRE_RATE);
    }
    else
        fireCooldown_ -= dt;

    isFiring_ = false;

    if (isLaunchingMissile_)
    {
        isLaunchingMissile_ = false;
    }
}
