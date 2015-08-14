#include "TitleState.hpp"

#include "ResourceIDs.hpp"
#include "StateStack.hpp"


TitleState::TitleState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
    , text_("Press Enter to continue or Escape to exit", context_.fontHolder.get(FontID::Sensation))
{
    context.textureHolder.load(TextureID::TitleScreen, "../Media/Textures/TitleScreen.png");

    background_.setTexture(context.textureHolder.get(TextureID::TitleScreen));

    textPos_.y = (context_.window.getSize().y / 2.f) - (text_.getLocalBounds().height / 2.f);
    textPos_.x = (context_.window.getSize().x / 2.f) - (text_.getLocalBounds().width / 2.f);

    text_.setPosition(textPos_);
}

void TitleState::render()
{
    context_.window.draw(background_);
    context_.window.draw(text_);
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
        pushOnStack(State::ID::Menu);
    }

    return true;
}
