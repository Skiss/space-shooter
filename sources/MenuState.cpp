#include "MenuState.hpp"

#include "StateStack.hpp"


MenuState::MenuState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void MenuState::render()
{

}

bool MenuState::update(const sf::Time& dt)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    return true;
}
