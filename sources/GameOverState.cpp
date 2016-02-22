#include "GameOverState.hpp"

#include "StateStack.hpp"


GameOverState::GameOverState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{
    gameOverText_.setFont(context.fontHolder.get(FontID::Sensation));
    gameOverText_.setString("Game Over!");
    gameOverText_.setCharacterSize(70);
    gameOverText_.setOrigin(gameOverText_.getLocalBounds().width / 2.f, gameOverText_.getLocalBounds().height / 2.f);
    gameOverText_.setPosition(context_.window.getView().getSize().x / 2.f, gameOverText_.getLocalBounds().height);

    background_.setSize(sf::Vector2f(context.window.getSize()));
    background_.setFillColor(sf::Color(0, 0, 0, 127));
}

void GameOverState::render()
{
    context_.window.setView(context_.window.getDefaultView());

    context_.window.draw(background_);
    context_.window.draw(gameOverText_);
}

bool GameOverState::update(const sf::Time& dt)
{
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape)
    {
        clearStack();
        pushOnStack(State::ID::Menu);
    }

    return false;
}
