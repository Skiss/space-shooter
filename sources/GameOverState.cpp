#include "GameOverState.hpp"

#include "StateStack.hpp"


GameOverState::GameOverState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{
}

void GameOverState::render()
{
    context_.window.setView(context_.window.getDefaultView());
}

bool GameOverState::update(const sf::Time& dt)
{
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Return)
    {
        clearStack();
        pushOnStack(State::ID::Menu);
    }

    return false;
}
