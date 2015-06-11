#ifndef GAME_H
#define GAME_H

#include "ResourceHolder.hpp"

#include "Aircraft.hpp"


enum class TextureID
{
    Eagle
};

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(const sf::Time& deltaTime);
    void render();

    void handleInputEvents(sf::Keyboard::Key key, bool isPressed);

    ResourceHolder<sf::Texture, TextureID> textureHolder_;

    sf::RenderWindow    window_;
    Aircraft*           player_ = nullptr;

    bool movingUp_ = false;
    bool movingDown_ = false;
    bool movingLeft_ = false;
    bool movingRight_ = false;

    const float playerSpeed_ = 200.f;
};

#endif