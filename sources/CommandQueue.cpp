#include "CommandQueue.hpp"

#include "Command.hpp"


void CommandQueue::push(Command* c)
{
    commandQueue_.push(c);
}

Command* CommandQueue::pop()
{
    Command* c = commandQueue_.front();
    commandQueue_.pop();

    return c;
}

bool CommandQueue::isEmpty() const
{
    return commandQueue_.empty();
}
