#include "PauseState.hpp"

#include "StateStack.hpp"


PauseState::PauseState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void PauseState::render()
{

}

bool PauseState::update()
{
    return true;
}

bool PauseState::handleEvent()
{
    return true;
}
