#include "Aircraft.hpp"

#include "Category.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TextNode.hpp"

#include <cassert>


unsigned Aircraft::idCpt_ = 0;


namespace
{
    std::vector<Data::AircraftData> data = Data::initAircraftData();
}

Aircraft::Aircraft(Type type, CommandQueue& commandQueue, const TextureHolder& textureHolder, const FontHolder& fontHolder, const sf::View& view)
    : Entity(data[type].hp)
    , id_(idCpt_++)
    , type_(type)
    , data_(data[type_])
    , sprite_(textureHolder.get(data_.textureID), data_.textureRect)
    , explosion_(textureHolder.get(TextureID::Explosion), sf::Vector2i(256, 256), 16, sf::seconds(1))
    , view_(view)
    , commandQueue_(commandQueue)
{
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    auto textNode = std::make_shared<TextNode>("", fontHolder);
    healthText_ = textNode.get();
    healthText_->setPosition(0, -50.f);

    // Init shoot commands
    fireCommand_.category_ = Category::SceneAirLayer;
    fireCommand_.action_ = [this, &textureHolder] (SceneNode* node, const sf::Time& dt)
    {
        createProjectile(*node, textureHolder, Projectile::AllyBullet);
    };

    launchMissileCommand_.category_ = Category::SceneAirLayer;
    launchMissileCommand_.action_ = [this, &textureHolder](SceneNode* node, const sf::Time& dt)
    {
        createProjectile(*node, textureHolder, Projectile::AllyMissile);
    };

    addChild(textNode);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isDestroyed())
        target.draw(explosion_, states);
    else
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

void Aircraft::setEnemyList(std::vector<std::shared_ptr<Aircraft>>& list)
{
    enemyList_ = &list;
}

void Aircraft::repair(int healAmount)
{
    hp_ += healAmount;

    if (hp_ > data_.maxHp)
        hp_ = data_.maxHp;
}

sf::FloatRect Aircraft::getBoundingBox() const
{
    return getWorldTransform().transformRect(sprite_.getGlobalBounds());
}

bool Aircraft::mustBeRemoved() const
{
    return isDestroyed() && explosion_.isFinished();
}

void Aircraft::createProjectile(SceneNode& node, const TextureHolder& textureHolder, Projectile::Type type)
{
    if (type & Projectile::Bullet)
        type = (isPlayer()) ? Projectile::AllyBullet : Projectile::EnemyBullet;
    else
        type = (isPlayer()) ? Projectile::AllyMissile : Projectile::EnemyMissile;

    int projectileDirection = (isPlayer()) ? -1 : 1;

    auto projectile = std::make_unique<Projectile>(type, textureHolder, commandQueue_, view_);

    projectile->setPosition(this->getPosition());
    projectile->setVelocity({0, projectile->getSpeed() * projectileDirection});

    if (type == Projectile::AllyMissile)
    {
        assert(enemyList_ != nullptr);

        if (!enemyList_->empty())
        {
            const std::shared_ptr<Aircraft>* target = nullptr;
            float maxDistance = std::numeric_limits<float>::max();

            for (const auto& e : *enemyList_)
            {
                float length = std::abs((e->getPosition().x - getPosition().x) + (e->getPosition().y - getPosition().y));

                if (length < maxDistance)
                    target = &e;
            }

            projectile->setMissileTarget(*target);
        }
    }

    node.addChild(std::move(projectile));
}

void Aircraft::updateCurrent(const sf::Time& dt)
{
    if (isDestroyed())
    {
        explosion_.update(dt);
        return;
    }

    updateMovements(dt);

    fireProjectiles(dt);

    Entity::updateCurrent(dt);
    healthText_->setText(std::to_string(hp_) + " HP");
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
        commandQueue_.push(fireCommand_);
        fireCooldown_ = sf::seconds(data_.fireRate);
    }
    else
        fireCooldown_ -= dt;

    isFiring_ = false;

    if (isLaunchingMissile_)
        commandQueue_.push(launchMissileCommand_);

    isLaunchingMissile_ = false;
}
