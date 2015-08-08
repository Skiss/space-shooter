#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Command.hpp"
#include "State.hpp"
#include "World.hpp"

#include <functional>


class CommandQueue;
class Entity;

class GameState : public State
{
public:
    GameState(StateStack& stateStack, State::Context context);

    void render() override;
    bool update(const sf::Time& dt) override;
    bool handleEvent(const sf::Event& event) override;

private:
    void createActions();

    World           world_;
    CommandQueue&   commandQueue_;

    const float playerSpeed_ = 200.f;

    std::function<void(Entity& e, sf::Vector2f vel)>    playerMoveFunc_;
    std::unordered_map<sf::Keyboard::Key, Command>      commandBinding_;
};

#endif