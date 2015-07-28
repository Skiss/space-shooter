#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.hpp"

#include <functional>
#include <memory>
#include <unordered_map>


class StateStack
{
public:
    StateStack(State::Context context);
    ~StateStack() = default;

    template <typename T>
    void registerState(State::ID id);

private:
    State::Context context_;
    std::unordered_map<State::ID, std::function<std::unique_ptr<State>()>> stateFactories_;
};


template <typename T>
void StateStack::registerState(State::ID id)
{
    stateFactories_[id] = [&context]()
    {
        return std::make_unique<T>(context_);
    };
}

#endif