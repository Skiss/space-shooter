#include "TitleState.hpp"

#include "ResourceIDs.hpp"
#include "StateStack.hpp"


TitleState::TitleState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
{
    context.textureHolder_.load(TextureID::TitleScreen, "../Media/Textures/TitleScreen.png");
    background_.setTexture(context.textureHolder_.get(TextureID::TitleScreen));
}

void TitleState::render()
{
    context_.window.draw(background_);
}

bool TitleState::update(const sf::Time& dt)
{
    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        popStack();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        popStack();
        pushOnStack(State::ID::Game);
    }

    return true;
}
