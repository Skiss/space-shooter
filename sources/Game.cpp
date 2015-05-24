#include "Game.hpp"

#include <iostream>


Game::Game()
    : window_(sf::VideoMode(640, 480), "Shooter")
{
    resourceHolder_.load(TextureID::Eagle, "../Media/Textures/Eagle.png");

    player_.setTexture(&resourceHolder_.get(TextureID::Eagle));
    player_.setRadius(40.f);
    player_.setPosition(100.f, 100.f);
    player_.setFillColor(sf::Color::Cyan);
}

Game::~Game()
{

}

void Game::run()
{
    sf::Clock clock;

    while (window_.isOpen())
    {
        sf::Time deltaTime = clock.restart();

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
        default:
            break;
        }
    }
}

void Game::update(const sf::Time& deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (movingUp_)
        movement.y -= playerSpeed_;
    if (movingDown_)
        movement.y += playerSpeed_;
    if (movingLeft_)
        movement.x -= playerSpeed_;
    if (movingRight_)
        movement.x += playerSpeed_;

    player_.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    window_.clear();
    window_.draw(player_);
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
