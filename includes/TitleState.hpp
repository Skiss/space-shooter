#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.hpp"

#include <SFML/Graphics.hpp>


class TitleState : public State
{
public:
    TitleState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update(const sf::Time& dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    sf::Sprite background_;
};

#endif