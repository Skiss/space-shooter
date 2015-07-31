#include "GameState.hpp"

#include "StateStack.hpp"


GameState::GameState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void GameState::render()
{

}

bool GameState::update()
{
    return true;
}

bool GameState::handleEvent()
{
    return true;
}
