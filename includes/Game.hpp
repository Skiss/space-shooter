#ifndef GAME_H
#define GAME_H

#include "World.hpp"
#include "Aircraft.hpp"


class Game
{
public:
    Game();
    ~Game() = default;

    void run();

private:
    void processEvents();
    void update(const sf::Time& deltaTime);
    void render();

    void handleInputEvents(sf::Keyboard::Key key, bool isPressed);

    TextureHolder       textureHolder_;
    sf::RenderWindow    window_;
    World               world_;

    bool movingUp_ = false;
    bool movingDown_ = false;
    bool movingLeft_ = false;
    bool movingRight_ = false;

    const float playerSpeed_ = 200.f;
};

#endif