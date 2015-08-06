#include "StateStack.hpp"


StateStack::StateStack(State::Context context)
    : context_(context)
{

}

void StateStack::pushState(State::ID id)
{
    pendingActions_.push_back(std::make_pair(Action::Push, id));
}

void StateStack::popState()
{
    pendingActions_.push_back(std::make_pair(Action::Pop, State::ID::None));
}

void StateStack::clearStates()
{
    pendingActions_.push_back(std::make_pair(Action::Clear, State::ID::None));
}

void StateStack::handleEvent(const sf::Event& event)
{
    for (auto& state : statesStack_)
        state->handleEvent(event);

    for (const auto& pair : pendingActions_)
    {
        switch (pair.first)
        {
        case Action::Push:
            statesStack_.push_back(stateFactories_[pair.second]());
            break;
        case Action::Pop:
            statesStack_.pop_back();
            break;
        case Action::Clear:
            statesStack_.clear();
            break;
        default:
            break;
        }
    }

    pendingActions_.clear();
}

void StateStack::update(const sf::Time& dt)
{
    for (auto& state : statesStack_)
        state->update(dt);
}

void StateStack::render()
{
    for (auto& state : statesStack_)
        state->render();
}

bool StateStack::isEmpty() const
{
    return statesStack_.empty() && pendingActions_.empty();
}
