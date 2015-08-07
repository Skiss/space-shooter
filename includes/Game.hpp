#ifndef GAME_H
#define GAME_H

#include "ResourceHolder.hpp"
#include "StateStack.hpp"

#include <SFML/Graphics.hpp>


class Game
{
public:
    Game();
    ~Game() = default;

    void run();

private:
    void processEvents();
    void update(const sf::Time& dt);
    void render();

    void updateFPS(const sf::Time& dt);

    void registerStates();
    void initFPSDisplay();

    FontHolder          fontHolder_;
    TextureHolder       textureHolder_;
    sf::RenderWindow    window_;

    sf::Text fps_;

    float elapsedTime_ =        0.f;
    const float playerSpeed_ =  100.f;

    StateStack stateStack_;
};

#endif