#ifndef COMMAND_H
#define COMMAND_H

#include <functional>


class SceneNode;

namespace sf
{ 
    class Time;
}

struct Command
{
    Command() = default;
    ~Command() = default;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    std::function<void(SceneNode*, const sf::Time& dt)> command_;
};

#endif