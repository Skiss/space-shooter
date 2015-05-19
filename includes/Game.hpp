#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>


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

    sf::RenderWindow    window_;
    sf::CircleShape     player_;

    bool movingUp_ = false;
    bool movingDown_ = false;
    bool movingLeft_ = false;
    bool movingRight_ = false;

    const float playerSpeed_ = 200.f;
};

#endif