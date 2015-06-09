#include "SceneNode.hpp"

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

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Nothing to do by default
}
