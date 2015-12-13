#include "World.hpp"

#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "SpriteNode.hpp"


static const float SQRT_TWO = std::sqrt(2.f);

namespace
{
    std::function<void(SceneNode*, const sf::Time& dt)> createRemoveMissileTargetAction(Aircraft* a)
    {
        return [=] (SceneNode* node, const sf::Time& dt)
        {
            Projectile* projectile = static_cast<Projectile*>(node);

            if (projectile->getMissileTarget() && projectile->getMissileTarget()->getID() == a->getID())
                projectile->setMissileTarget(nullptr);
        };
    }
}


World::World(sf::RenderWindow& window, TextureHolder& textureHolder, const FontHolder& fontHolder)
    : textureHolder_(textureHolder)
    , fontHolder_(fontHolder)
    , window_(window)
    , sceneGraph_(nullptr)
    , player_(nullptr)
    , view_(window_.getDefaultView())
    , worldBounds_(0.f, 0.f, view_.getSize().x, 2000.f)
    , playerSpawnPos_(view_.getSize().x / 2.f, worldBounds_.height - view_.getSize().y / 2.f)
    , scrollSpeed_(-50.f)
{
    buildScene();

    view_.setCenter(playerSpawnPos_);
}

void World::update(const sf::Time& dt)
{
    view_.move(0.f, scrollSpeed_ * dt.asSeconds());

    player_->setVelocity(sf::Vector2f(0.f, 0.f));

    spawnEnemies();
    destroyEnemies();

    while (!commandQueue_.isEmpty())
        sceneGraph_->execCommand(commandQueue_.pop(), dt);

    correctVelocity();

    sceneGraph_->update(dt);
}

void World::render()
{
    window_.setView(view_);
    window_.draw(*sceneGraph_);
}

CommandQueue& World::getCommandQueue()
{
    return commandQueue_;
}

void World::buildScene()
{
    // Root node
    sceneGraph_ = std::make_unique<SceneNode>();

    // Background layer
    auto bgLayer = std::make_unique<SceneNode>();
    layers_[Layer::BACKGROUND] = bgLayer.get();
    sceneGraph_->addChild(std::move(bgLayer));

    // Air layer
    auto airLayer = std::make_unique<SceneNode>(Category::SceneAirLayer);
    layers_[Layer::AIR] = airLayer.get();
    sceneGraph_->addChild(std::move(airLayer));

    // Player node
    auto player = std::make_unique<Aircraft>(Aircraft::Eagle, commandQueue_, textureHolder_, fontHolder_);
    player->setPosition(playerSpawnPos_);
    player->setVelocity(0.f, scrollSpeed_);
    player->setEnemyList(activeEnemies_);
    player_ = player.get();
    layers_[Layer::AIR]->addChild(std::move(player));
    
    // Background texture has to be repeated
    auto& texture = textureHolder_.get(TextureID::Background);
    sf::IntRect textureRect(worldBounds_);
    texture.setRepeated(true);

    // Background node
    auto bg = std::make_unique<SpriteNode>(textureHolder_.get(TextureID::Background), textureRect);
    bg->setPosition(worldBounds_.left, worldBounds_.top);
    layers_[Layer::BACKGROUND]->addChild(std::move(bg));

    // Adding spawn positions
    addSpawnPoints();
}

void World::correctVelocity() const
{
    // Correcting the diagonal velocity, if any
    if (player_->getVelocity().x != 0.f && player_->getVelocity().y != 0.f)
        player_->setVelocity(player_->getVelocity() / SQRT_TWO);

    // Matching at least the scroll speed
    player_->accelerate(sf::Vector2f(0.f, scrollSpeed_));
}

bool World::isInsideSpawnZone(const SpawnPosition& pos) const
{
    const float topScreen = view_.getCenter().y - window_.getSize().y / 2.f;

    if (pos.y <= topScreen && pos.y >= topScreen - 50.f)
        return true;

    return false;
}

bool World::isOutOfGameZone(const sf::Vector2f& pos) const
{
    const float bottomScreen = view_.getCenter().y + window_.getSize().y / 2.f;

    if (pos.y > bottomScreen + 50.f)
        return true;

    return false;
}

void World::addSpawnPoints()
{
    float xCenter = view_.getCenter().x;

    enemiesSpawnPos_.emplace_back(Aircraft::Raptor, xCenter, 1300.f);
    enemiesSpawnPos_.emplace_back(Aircraft::Raptor, xCenter + 100.f, 1100.f);
    enemiesSpawnPos_.emplace_back(Aircraft::Raptor, xCenter - 100.f, 900.f);
    enemiesSpawnPos_.emplace_back(Aircraft::Raptor, xCenter, 1500.f);

    enemiesSpawnPos_.emplace_back(Aircraft::Avenger, xCenter + 50.f, 500.f);
    enemiesSpawnPos_.emplace_back(Aircraft::Avenger, xCenter - 50.f, 500.f);
    
    std::sort(begin(enemiesSpawnPos_),
              end(enemiesSpawnPos_),
              [](const SpawnPosition& sp1, const SpawnPosition& sp2)
    {
        return sp1.y < sp2.y;
    });
}

void World::spawnEnemies()
{
    if (!enemiesSpawnPos_.empty() && isInsideSpawnZone(enemiesSpawnPos_.back()))
    {
        auto enemy = std::make_unique<Aircraft>(enemiesSpawnPos_.back().type, commandQueue_, textureHolder_, fontHolder_);
        enemy->setPosition(enemiesSpawnPos_.back().x, enemiesSpawnPos_.back().y);
        enemy->setRotation(180.f);
        activeEnemies_.push_back(enemy.get());
        layers_[Layer::AIR]->addChild(std::move(enemy));

        enemiesSpawnPos_.pop_back();
    }
}

void World::destroyEnemies()
{
    queuededCommands_.clear();

    for (auto e : activeEnemies_)
    {
        if (e->isOutOfGameZone())
        {
            e->destroy();
            layers_[Layer::AIR]->removeChild(*e);
        }

        if (isOutOfGameZone(e->getPosition()))
        {
            e->setIsOutOfGameZone(true);
            queuededCommands_.emplace_back(createRemoveMissileTargetAction(e), Category::AllyProjectile);
            commandQueue_.push(queuededCommands_.back());
        }
    }

    auto iter = std::remove_if(begin(activeEnemies_), end(activeEnemies_), [](const Aircraft* a)
    {
        return a->isDestroyed();
    });
    activeEnemies_.erase(iter, end(activeEnemies_));
}
