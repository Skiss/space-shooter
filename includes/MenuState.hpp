#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.hpp"

#include <SFML/Graphics.hpp>


class MenuState : public State
{
public:
    MenuState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update(const sf::Time& dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    void initOptionsText();

    sf::Sprite              background_;
    std::vector<sf::Text>   options_;
    unsigned                optionIdx_ = 0;
};

#endif