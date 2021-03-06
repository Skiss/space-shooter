#include "SceneNode.hpp"

#include "Command.hpp"

#include <algorithm>


SceneNode::SceneNode(Category::Type type)
    : type_(type)
{ }

void SceneNode::addChild(SceneNodePtr child)
{
    child->parent_ = this;
    children_.push_back(child);
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
    return type_;
}

void SceneNode::getCollisionList(SceneNode& root, std::set<SceneNodePair>& collisionList)
{
    checkNodeCollisions(root, collisionList);

    for (const auto& c : root.children_)
    {
        checkNodeCollisions(*c, collisionList);
        c->getCollisionList(*c, collisionList);
    }
}

void SceneNode::checkNodeCollisions(SceneNode& root, std::set<SceneNodePair>& set)
{
    if (this != &root && this->getBoundingBox().intersects(root.getBoundingBox()))
        set.insert(std::minmax(this, &root));

    for (const auto& c : children_)
        c->checkNodeCollisions(root, set);
}

sf::FloatRect SceneNode::getBoundingBox() const
{
    return sf::FloatRect();
}

void SceneNode::removeMarkedNodes()
{
    auto iter = std::remove_if(begin(children_), end(children_), [](const SceneNodePtr& node)
    {
        return node->mustBeRemoved();
    });

    children_.erase(iter, end(children_));

    for (auto& c : children_)
        c->removeMarkedNodes();
}
