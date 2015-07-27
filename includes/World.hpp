#ifndef WORLD_H
#define WORLD_H

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics.hpp>

#include <array>


enum class TextureID
{
    Background,
    Eagle
};

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;

class SceneNode;
class Aircraft;

class World
{
public:
    World(sf::RenderWindow& window, TextureHolder& textureHolder);
    ~World() = default;

    World(const World&) = delete;
    World& operator=(const World&) = delete;

    void update(const sf::Time& dt);
    void render();

    CommandQueue& getCommandQueue();

private:
    enum Layer
    {
        BACKGROUND,
        AIR,
        LAYER_COUNT
    };

    void loadTextures();
    void buildScene();
    void correctingVelocity() const;


    TextureHolder&                              textureHolder_;
    sf::RenderWindow&                           window_;
    CommandQueue                                commandQueue_;
    std::unique_ptr<SceneNode>                  sceneGraph_;
    Aircraft*                                   player_;
    std::array<SceneNode*, Layer::LAYER_COUNT>  layers_;
    sf::View                                    view_;
    sf::FloatRect                               worldBounds_;
    sf::Vector2f                                playerSpawnPos_;
    float                                       scrollSpeed_;
};

#endif