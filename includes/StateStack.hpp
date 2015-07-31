#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.hpp"

#include <functional>
#include <memory>
#include <unordered_map>


namespace sf
{
    class Event;
    class Time;
}

class StateStack
{
public:
    enum class Action
    {
        Push,
        Pop,
        Clear
    };

    StateStack(State::Context context);
    ~StateStack() = default;

    template <typename T>
    void registerState(State::ID id);

    void pushState(State::ID id);
    void popState();
    void clearStates();

    void handleEvent(const sf::Event& event);
    void update(const sf::Time& dt);
    void render();

private:
    State::Context context_;

    std::vector<std::unique_ptr<State>> statesStack_;

    std::unordered_map<State::ID, std::function<std::unique_ptr<State>()>>  stateFactories_;
    std::vector<std::pair<Action, State::ID>>                               pendingActions_;
};


template <typename T>
void StateStack::registerState(State::ID id)
{
    stateFactories_[id] = [this]()
    {
        return std::make_unique<T>(*this, context_);
    };
}

#endif