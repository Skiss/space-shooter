#include "PauseState.hpp"

#include "StateStack.hpp"


PauseState::PauseState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
    , background_()
{
    background_.setSize(sf::Vector2f(context.window.getSize()));
    background_.setFillColor(sf::Color(0, 0, 0, 127));
}

void PauseState::render()
{
    context_.window.draw(background_);
}

bool PauseState::update(const sf::Time& dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    return false;
}
