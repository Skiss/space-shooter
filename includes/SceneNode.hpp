#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>


class SceneNode : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::unique_ptr<SceneNode> SceneNodePtr;

    SceneNode() = default;
    SceneNode(const SceneNode&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;

    void addChild(SceneNodePtr child);
    void removeChild(const SceneNode& child);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    SceneNode*                  parent_ = nullptr;
    std::vector<SceneNodePtr>   children_;
};

#endif