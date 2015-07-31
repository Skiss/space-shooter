#include "MenuState.hpp"

#include "StateStack.hpp"


MenuState::MenuState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{

}

void MenuState::render()
{

}

bool MenuState::update()
{
    return true;
}

bool MenuState::handleEvent()
{
    return true;
}
