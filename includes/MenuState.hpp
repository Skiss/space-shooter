#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.hpp"


class MenuState : public State
{
public:
    MenuState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update() override;
    bool handleEvent() override;
};

#endif