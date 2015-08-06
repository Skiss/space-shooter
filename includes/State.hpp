#ifndef STATE_H
#define STATE_H

#include "ResourceHolder.hpp"
#include "ResourceIDs.hpp"


namespace sf
{
    class Event;
    class RenderWindow;
    class Time;
}

class StateStack;

class State
{
public:
    enum class ID
    {
        None,
        Title,
        Menu,
        Game,
        Pause
    };

    struct Context
    {
        sf::RenderWindow&   window;
        TextureHolder&      textureHolder_;
    };

    State(StateStack& stateStack, Context context);
    virtual ~State() = default;

    virtual void render() = 0;
    virtual bool update(const sf::Time& dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

private:
    Context     context_;
    StateStack& stack_;
};

#endif