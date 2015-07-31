#include "State.hpp"

#include "StateStack.hpp"


State::State(StateStack& stateStack, Context context)
    : context_(context)
    , stack_(stateStack)
{

}
