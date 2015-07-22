#include "SceneNode.hpp"

#include "Command.hpp"

#include <algorithm>


void SceneNode::addChild(SceneNodePtr child)
{
    child->parent_ = this;
    children_.push_back(std::move(child));
}

void SceneNode::removeChild(const SceneNode& child)
{
    children_.erase(std::remove_if(begin(children_), end(children_), 
        [&](const SceneNodePtr& node) 
    { 
        return node.get() == &child;
    }));
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);

    for (const auto& c : children_)
        c->draw(target, states);
}

void SceneNode::update(const sf::Time& dt)
{
    updateCurrent(dt);

    for (const auto& c : children_)
        c->update(dt);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Nothing to do by default
}

void SceneNode::updateCurrent(const sf::Time& dt)
{
    // Nothing to do here either
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform res = sf::Transform::Identity;

    for (auto node = this; node != nullptr; node = node->parent_)
        res = node->getTransform() * res;

    return res;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::execCommand(const Command& c, const sf::Time& dt)
{
    if (getCategory() & c.category_)
        c.action_(this, dt);

    for (const auto& child : children_)
        child->execCommand(c, dt);
}

unsigned SceneNode::getCategory() const
{
    return Category::Empty;
}
