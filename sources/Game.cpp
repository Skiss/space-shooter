#include "Game.hpp"

#include "Command.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "TitleState.hpp"

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
    , stateStack_({window_})
    , playerMoveFunc_([] (Entity& e, sf::Vector2f vel) { e.accelerate(vel); })
{
    createActions();
    registerStates();
    initFPSDisplay();

    stateStack_.pushState(State::ID::Game);
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
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window_.close();

    for (auto& pair : commandBinding_)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
            commandQueue_.push(&pair.second);
    }
}

void Game::update(const sf::Time& dt)
{
    world_.update(dt);

    updateFPS(dt);
}

void Game::render()
{
    window_.clear();

    world_.render();

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

void Game::createActions()
{
    commandBinding_[sf::Keyboard::Right].action_ = createAction<Entity>(std::bind(playerMoveFunc_, std::placeholders::_1, sf::Vector2f(playerSpeed_, 0.f)));
    commandBinding_[sf::Keyboard::Right].category_ = Category::PlayerEntity;

    commandBinding_[sf::Keyboard::Left].action_ = createAction<Entity>(std::bind(playerMoveFunc_, std::placeholders::_1, sf::Vector2f(-playerSpeed_, 0.f)));
    commandBinding_[sf::Keyboard::Left].category_ = Category::PlayerEntity;

    commandBinding_[sf::Keyboard::Up].action_ = createAction<Entity>(std::bind(playerMoveFunc_, std::placeholders::_1, sf::Vector2f(0.f, -playerSpeed_)));
    commandBinding_[sf::Keyboard::Up].category_ = Category::PlayerEntity;

    commandBinding_[sf::Keyboard::Down].action_ = createAction<Entity>(std::bind(playerMoveFunc_, std::placeholders::_1, sf::Vector2f(0.f, playerSpeed_)));
    commandBinding_[sf::Keyboard::Down].category_ = Category::PlayerEntity;
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
    font_.loadFromFile("../Media/Sansation.ttf");

    fps_.setFont(font_);
    fps_.setStyle(sf::Text::Bold);
    fps_.setColor(sf::Color::Red);
    fps_.setCharacterSize(16);
    fps_.setPosition(10.f, 10.f);
}
