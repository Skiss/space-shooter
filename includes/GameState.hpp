#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.hpp"


class GameState : public State
{
public:
    GameState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update() override;
    bool handleEvent() override;
};

#endif