#include "Game.hpp"

#include "Command.hpp"

#include <sstream>


namespace
{
    template <typename TargetType>
    std::function<void(SceneNode*, const sf::Time& dt)> createAction(std::function<void(Entity& e)> func)
    {
        return [=] (SceneNode* node, const sf::Time& )
        {
            assert(dynamic_cast<TargetType*>(node));

            func(static_cast<TargetType&>(*node));
        };
    }
}

Game::Game()
    : window_(sf::VideoMode(640, 480), "Shooter")
    , world_(window_, textureHolder_)
    , commandQueue_(world_.getCommandQueue())
{
    playerMoveFunc_ = [=] (Entity& e, sf::Vector2f vel)
    {
        e.accelerate(vel);
    };

    commandBinding_[sf::Keyboard::Left].action_ = createAction<Entity>(std::bind(playerMoveFunc_, std::placeholders::_1, sf::Vector2f(playerSpeed_, 0.f)));
    commandBinding_[sf::Keyboard::Left].category_ = Category::PlayerEntity;

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
    if (key == sf::Keyboard::A && isPressed == true)
        commandQueue_.push(&commandBinding_[sf::Keyboard::Left]);
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
