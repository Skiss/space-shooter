#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.hpp"

#include <SFML/Graphics.hpp>


class GameOverState : public State
{
public:
    GameOverState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update(const sf::Time& dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
};

#endif