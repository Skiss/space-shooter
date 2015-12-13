#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include "Command.hpp"

#include <queue>


class CommandQueue
{
public:
    CommandQueue() = default;
    ~CommandQueue() = default;

    CommandQueue(const CommandQueue&) = delete;
    CommandQueue& operator=(const CommandQueue&) = delete;

    void push(const Command& c);
    Command pop();

    bool isEmpty() const;
    int size() const { return commandQueue_.size();  }

private:
    std::queue<Command> commandQueue_;
};

#endif
