#ifndef WORLD_H
#define WORLD_H

#include "CommandQueue.hpp"
#include "ResourceIDs.hpp"

#include <SFML/Graphics.hpp>

#include <array>
#include <memory>


class SceneNode;
class Aircraft;

class World
{
public:
    World(sf::RenderWindow& window, TextureHolder& textureHolder, const FontHolder& fontHolder);
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

    void buildScene();
    void correctingVelocity() const;


    TextureHolder&                              textureHolder_;
    const FontHolder&                           fontHolder_;
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