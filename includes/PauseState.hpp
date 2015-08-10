#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.hpp"

#include <SFML/Graphics.hpp>


class PauseState : public State
{
public:
    PauseState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update(const sf::Time& dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::RectangleShape  background_;
    sf::Text            pausedText_;
    sf::Text            instructionsText_;
};

#endif