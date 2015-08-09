#include "MenuState.hpp"

#include "StateStack.hpp"


MenuState::MenuState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
    , background_(context.textureHolder_.get(TextureID::TitleScreen))
{
    initOptionsText();
}

void MenuState::render()
{
    context_.window.draw(background_);

    for (unsigned i = 0; i < options_.size(); ++i)
    {
        if (i == optionIdx_)
            options_.at(i).setColor(sf::Color::Red);
        else
            options_.at(i).setColor(sf::Color::White);

        context_.window.draw(options_.at(i));
    }
}

bool MenuState::update(const sf::Time& dt)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Escape)
        popStack();

    if (event.key.code == sf::Keyboard::Down)
        optionIdx_ = (optionIdx_ < 1) ? ++optionIdx_ : 0;

    if (event.key.code == sf::Keyboard::Up)
        optionIdx_ = (optionIdx_ > 0) ? --optionIdx_ : 1;

    if (event.key.code == sf::Keyboard::Return)
    {
        popStack();

        if (optionIdx_ == 0)
            pushOnStack(State::ID::Game);
    }

    return true;
}

void MenuState::initOptionsText()
{
    sf::Text option;

    option.setFont(context_.fontHolder_.get(FontID::Sensation));
    option.setString("Play");
    option.setOrigin(option.getLocalBounds().width / 2.f, option.getLocalBounds().height / 2.f);
    option.setPosition(context_.window.getView().getSize() / 2.f);
    options_.push_back(option);

    option.setString("Exit");
    option.setPosition(option.getPosition().x, option.getPosition().y + 50);
    options_.push_back(option);
}
