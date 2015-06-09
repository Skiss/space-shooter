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
