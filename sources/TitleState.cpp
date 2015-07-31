#include "TitleState.hpp"

#include "StateStack.hpp"


TitleState::TitleState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void TitleState::render()
{

}

bool TitleState::update()
{
    return true;
}

bool TitleState::handleEvent()
{
    return true;
}
