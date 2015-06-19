#ifndef WORLD_H
#define WORLD_H

#include "ResourceHolder.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics.hpp>


enum class TextureID
{
    Background,
    Eagle
};

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;

class World
{
public:
    World(sf::RenderWindow& window, TextureHolder& textureHolder);
    ~World() = default;

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    void update();
    void render();

private:
    void loadTextures();

    TextureHolder&              textureHolder_;
    sf::RenderWindow&           window_;
    std::unique_ptr<SceneNode>  sceneGraph_;
    sf::View                    view_;
};

#endif