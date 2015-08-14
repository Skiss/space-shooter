#include "PauseState.hpp"

#include "StateStack.hpp"


PauseState::PauseState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
    , background_()
{
    background_.setSize(sf::Vector2f(context.window.getSize()));
    background_.setFillColor(sf::Color(0, 0, 0, 127));

    pausedText_.setFont(context_.fontHolder.get(FontID::Sensation));
    pausedText_.setString("Game Paused");
    pausedText_.setCharacterSize(70);
    pausedText_.setOrigin(pausedText_.getLocalBounds().width / 2.f, pausedText_.getLocalBounds().height / 2.f);
    pausedText_.setPosition(context_.window.getView().getSize().x / 2.f, pausedText_.getLocalBounds().height);

    instructionsText_.setFont(context_.fontHolder.get(FontID::Sensation));
    instructionsText_.setString("Press Backspace to return to the menu");
    instructionsText_.setCharacterSize(32);
    instructionsText_.setOrigin(instructionsText_.getLocalBounds().width / 2.f, instructionsText_.getLocalBounds().height / 2.f);
    instructionsText_.setPosition(context_.window.getView().getSize().x / 2.f, context_.window.getView().getSize().y / 2.f);
}

void PauseState::render()
{
    context_.window.setView(context_.window.getDefaultView());

    context_.window.draw(background_);
    context_.window.draw(pausedText_);
    context_.window.draw(instructionsText_);
}

bool PauseState::update(const sf::Time& dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::BackSpace)
    {
        clearStack();
        pushOnStack(State::ID::Menu);
    }

    if (event.key.code == sf::Keyboard::Escape)
        popStack();

    return false;
}
