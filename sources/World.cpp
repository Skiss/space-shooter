#include "World.hpp"

#include "Aircraft.hpp"
#include "SpriteNode.hpp"


World::World(sf::RenderWindow& window, TextureHolder& textureHolder)
    : textureHolder_(textureHolder)
    , window_(window)
    , sceneGraph_(nullptr)
    , player_(nullptr)
    , view_(window_.getDefaultView())
    , worldBounds_(0.f, 0.f, view_.getSize().x, 2000.f)
    , playerSpawnPos_(view_.getSize().x / 2.f, worldBounds_.height - view_.getSize().y / 2.f)
    , scrollSpeed_(-50.f)
{
    loadTextures();
    buildScene();

    view_.setCenter(playerSpawnPos_);
}


void World::update(const sf::Time& dt)
{
    view_.move(0.f, scrollSpeed_ * dt.asSeconds());

    while (!commandQueue_.isEmpty())
        sceneGraph_->execCommand(*commandQueue_.pop(), dt);

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

void World::loadTextures()
{
    textureHolder_.load(TextureID::Background, "../Media/Textures/Desert.png");
    textureHolder_.load(TextureID::Eagle, "../Media/Textures/Eagle.png");
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
    auto airLayer = std::make_unique<SceneNode>();
    layers_[Layer::AIR] = airLayer.get();
    sceneGraph_->addChild(std::move(airLayer));

    // Player node
    auto player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textureHolder_.get(TextureID::Eagle));
    player->setPosition(playerSpawnPos_);
    player->setVelocity(0.f, scrollSpeed_);
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
}
