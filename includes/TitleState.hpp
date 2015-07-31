#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.hpp"


class TitleState : public State
{
public:
    TitleState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update() override;
    bool handleEvent() override;
};

#endif