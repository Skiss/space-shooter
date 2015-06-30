#include "World.hpp"

#include "Aircraft.hpp"
#include "SpriteNode.hpp"


World::World(sf::RenderWindow& window, TextureHolder& textureHolder)
    : textureHolder_(textureHolder)
    , window_(window)
    , sceneGraph_(nullptr)
    , view_(window_.getDefaultView())
{
    loadTextures();
    buildScene();
}


void World::update(const sf::Time& dt)
{
    sceneGraph_->update(dt);
}

void World::render()
{
    window_.setView(view_);
    window_.draw(*sceneGraph_);
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
    player->setPosition(320, 240);
    auto player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textureHolder_.get(TextureID::Eagle));
    layers_[Layer::AIR]->addChild(std::move(player));

    // Background node
    auto bg = std::make_unique<SpriteNode>(textureHolder_.get(TextureID::Background));
    layers_[Layer::BACKGROUND]->addChild(std::move(bg));
}
