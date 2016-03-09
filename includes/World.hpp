#ifndef WORLD_H
#define WORLD_H

#include "Aircraft.hpp"
#include "CommandQueue.hpp"


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

    bool isGameOver() const;

private:
    struct SpawnPosition
    {
        SpawnPosition(Aircraft::Type type, float x, float y)
            : type(type)
            , x(x)
            , y(y)
        {}

        Aircraft::Type  type;
        float           x;
        float           y;
    };

    enum Layer
    {
        BACKGROUND,
        AIR,
        LAYER_COUNT
    };

    void buildScene();
    void handleCollisions();
    void correctVelocity() const;
    bool isInsideSpawnZone(const SpawnPosition& pos) const;
    bool isOutOfGameZone(const sf::Vector2f& pos) const;
    void addSpawnPoints();
    void spawnEnemies();
    void destroyEnemies();


    TextureHolder&                              textureHolder_;
    const FontHolder&                           fontHolder_;
    sf::RenderWindow&                           window_;
    CommandQueue                                commandQueue_;
    std::shared_ptr<SceneNode>                  sceneGraph_;
    Aircraft*                                   player_;
    std::array<SceneNode*, Layer::LAYER_COUNT>  layers_;
    sf::View                                    view_;
    sf::FloatRect                               worldBounds_;
    sf::Vector2f                                playerSpawnPos_;
    float                                       scrollSpeed_;
    std::vector<SpawnPosition>                  enemiesSpawnPos_;
    std::vector<std::shared_ptr<Aircraft>>      activeEnemies_ ;
    std::vector<Command>                        queuededCommands_;
};

#endif