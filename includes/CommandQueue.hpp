#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

#include <queue>


struct Command;

class CommandQueue
{
public:
    CommandQueue() = default;
    ~CommandQueue() = default;

    CommandQueue(const CommandQueue&) = delete;
    CommandQueue& operator=(const CommandQueue&) = delete;

    void push(Command* c);
    Command* pop();

    bool isEmpty() const;

private:
    std::queue<Command*> commandQueue_;
};

#endif