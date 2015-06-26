#include "World.hpp"

#include "Aircraft.hpp"


World::World(sf::RenderWindow& window, TextureHolder& textureHolder)
    : textureHolder_(textureHolder)
    , window_(window)
    , sceneGraph_(nullptr)
    , view_(window_.getDefaultView())
{
    loadTextures();
    buildScene();
}


void World::update()
{

}

void World::render()
{
    window_.setView(view_);
    window_.draw(*sceneGraph_);
}

void World::loadTextures()
{
    textureHolder_.load(TextureID::Background, "../Media/Textures/dry.jpg");
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
    layers_[Layer::AIR]->addChild(std::move(player));
}
