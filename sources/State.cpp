#include "State.hpp"

#include "StateStack.hpp"


State::State(StateStack& stateStack, Context context)
    : context_(context)
    , stack_(stateStack)
{

}

void State::pushOnStack(State::ID id)
{
    stack_.pushState(id);
}

void State::popStack()
{
    stack_.popState();
}

void State::clearStack()
{
    stack_.clearStates();
}
