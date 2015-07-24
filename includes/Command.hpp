#ifndef COMMAND_H
#define COMMAND_H


#include "Category.hpp"

#include <functional>


class SceneNode;

namespace sf
{
    class Time;
}

struct Command
{
    Command() = default;
    Command(std::function<void(SceneNode*, const sf::Time& dt)> action, Category::Type category)
        : action_(action)
        , category_(category)
    {}
    ~Command() = default;

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    std::function<void(SceneNode*, const sf::Time& dt)> action_;
    Category::Type                                      category_ = Category::Empty;
};

#endif