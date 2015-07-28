#ifndef STATE_H
#define STATE_H


namespace sf
{
    class RenderWindow;
}

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

    State(Context context);
    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update() = 0;
    virtual bool handleEvent() = 0;

private:
    Context context_;
};

#endif