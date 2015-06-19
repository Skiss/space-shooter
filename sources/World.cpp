#include "World.hpp"

#include "Aircraft.hpp"


World::World(sf::RenderWindow& window, TextureHolder& textureHolder)
    : textureHolder_(textureHolder)
    , window_(window)
    , sceneGraph_(nullptr)
    , view_(window_.getDefaultView())
{
    loadTextures();

    sceneGraph_ = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textureHolder_.get(TextureID::Eagle));
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
