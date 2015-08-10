#include "GameState.hpp"

#include "Entity.hpp"
#include "SceneNode.hpp"
#include "StateStack.hpp"


namespace
{
    template <typename TargetType>
    std::function<void(SceneNode*, const sf::Time& dt)> createAction(std::function<void(Entity& e)> func)
    {
        return [=](SceneNode* node, const sf::Time&)
        {
            assert(dynamic_cast<TargetType*>(node));

            func(static_cast<TargetType&>(*node));
        };
    }
}

GameState::GameState(StateStack& stateStack, State::Context context)
    : State(stateStack, context)
    , world_(context.window, context.textureHolder_)
    , playerMoveFunc_([] (Entity& e, sf::Vector2f vel) { e.accelerate(vel); })
    , commandQueue_(world_.getCommandQueue())
{
    createActions();
}

void GameState::render()
{
    world_.render();
}

bool GameState::update(const sf::Time& dt)
{
    world_.update(dt);

    handleRealTimeInput();

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        pushOnStack(State::ID::Pause);

    return true;
}

void GameState::handleRealTimeInput()
{
    for (auto& pair : commandBinding_)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
            commandQueue_.push(&pair.second);
    }
}

void GameState::createActions()
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
