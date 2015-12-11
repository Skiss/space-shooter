#ifndef COMMAND_H
#define COMMAND_H


#include "Category.hpp"
#include "SceneNode.hpp"

#include <functional>


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

    Command(Command&& c)
        : action_(c.action_)
        , category_(c.category_)
    { }

    Command(const Command&) = delete;
    Command& operator=(const Command&) = delete;

    std::function<void(SceneNode*, const sf::Time& dt)> action_;
    Category::Type                                      category_ = Category::Empty;
};

#endif