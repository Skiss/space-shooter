#include "Game.hpp"

#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "TitleState.hpp"

#include <sstream>


Game::Game()
    : window_(sf::VideoMode(640, 480), "Shooter")
    , stateStack_({window_, textureHolder_, fontHolder_})
{
    fontHolder_.load(FontID::Sensation, "../Media/Fonts/Sansation.ttf");

    registerStates();
    initFPSDisplay();

    stateStack_.pushState(State::ID::Title);
}

void Game::run()
{
    sf::Clock clock;

    while (window_.isOpen() && !stateStack_.isEmpty())
    {
        sf::Time deltaTime = clock.restart();
        elapsedTime_ += deltaTime.asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (window_.pollEvent(event))
    {
        stateStack_.handleEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        }
    }
}

void Game::update(const sf::Time& dt)
{
    stateStack_.update(dt);

    updateFPS(dt);
}

void Game::render()
{
    window_.clear();

    stateStack_.render();

    window_.setView(window_.getDefaultView());
    window_.draw(fps_);
    window_.display();
}

void Game::updateFPS(const sf::Time& dt)
{
    if (elapsedTime_ > 1.f)
    {
        std::stringstream ss;
        ss << static_cast<int>(1.f / dt.asSeconds());
        fps_.setString("FPS: " + ss.str());

        elapsedTime_ = 0.f;
    }
}

void Game::registerStates()
{
    stateStack_.registerState<TitleState>(State::ID::Title);
    stateStack_.registerState<GameState>(State::ID::Game);
    stateStack_.registerState<MenuState>(State::ID::Menu);
    stateStack_.registerState<PauseState>(State::ID::Pause);
}

void Game::initFPSDisplay()
{
    fps_.setFont(fontHolder_.get(FontID::Sensation));
    fps_.setStyle(sf::Text::Bold);
    fps_.setColor(sf::Color::Red);
    fps_.setCharacterSize(fpsSize_);
    fps_.setPosition(fpsPos_);
}
