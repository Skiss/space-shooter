#ifndef STATE_H
#define STATE_H


namespace sf
{
    class RenderWindow;
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
        sf::RenderWindow& window;
    };

    State(StateStack& stateStack, Context context);
    virtual ~State() = default;

    virtual void render() = 0;
    virtual bool update() = 0;
    virtual bool handleEvent() = 0;

private:
    Context     context_;
    StateStack& stack_;
};

#endif