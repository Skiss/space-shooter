#include "Game.hpp"

#include <sstream>


Game::Game()
    : window_(sf::VideoMode(640, 480), "Shooter")
    , world_(window_, textureHolder_)
{
    initFPSDisplay();
}

void Game::run()
{
    sf::Clock clock;

    while (window_.isOpen())
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
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::KeyPressed:
            handleInputEvents(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleInputEvents(event.key.code, false);
            break;
        }
    }
}

void Game::update(const sf::Time& deltaTime)
{
    world_.update(deltaTime);

    if (elapsedTime_ > 1.f)
    {
        std::stringstream ss;
        ss << static_cast<int>(1.f / deltaTime.asSeconds());
        fps_.setString("FPS: " + ss.str());

        elapsedTime_ = 0.f;
    }
}

void Game::render()
{
    window_.clear();

    world_.render();

    window_.setView(window_.getDefaultView());
    window_.draw(fps_);
    window_.display();
}

void Game::handleInputEvents(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        movingUp_ = isPressed;
    if (key == sf::Keyboard::A)
        movingLeft_ = isPressed;
    if (key == sf::Keyboard::S)
        movingDown_ = isPressed;
    if (key == sf::Keyboard::D)
        movingRight_ = isPressed;

    if (!isPressed)
    {
        if (key == sf::Keyboard::Escape)
            window_.close();
    }
}

void Game::initFPSDisplay()
{
    font_.loadFromFile("../Media/Sansation.ttf");

    fps_.setFont(font_);
    fps_.setStyle(sf::Text::Bold);
    fps_.setColor(sf::Color::Red);
    fps_.setCharacterSize(16);
    fps_.setPosition(10.f, 10.f);
}
