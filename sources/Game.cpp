#include "Game.hpp"


Game::Game()
    : window_(sf::VideoMode(640, 480), "Shooter")
{
    player_.setRadius(40.f);
    player_.setPosition(100.f, 100.f);
    player_.setFillColor(sf::Color::Cyan);
}

Game::~Game()
{

}

void Game::run()
{
    while (window_.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

void Game::update()
{

}

void Game::render()
{
    window_.clear();
    window_.draw(player_);
    window_.display();
}
