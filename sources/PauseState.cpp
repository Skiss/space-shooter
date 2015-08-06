#include "PauseState.hpp"

#include "StateStack.hpp"


PauseState::PauseState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void PauseState::render()
{

}

bool PauseState::update(const sf::Time& dt)
{
    return true;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    return true;
}
