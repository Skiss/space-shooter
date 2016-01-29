#ifndef SCENENODE_H
#define SCENENODE_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/System/Time.hpp>

#include "Category.hpp"

#include <memory>
#include <set>
#include <vector>


struct Command;

class SceneNode : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::unique_ptr<SceneNode> SceneNodePtr;
    typedef std::pair<const SceneNode*, const SceneNode*> SceneNodePair;

    SceneNode(Category::Type type = Category::Empty);
    SceneNode(const SceneNode&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;

    void addChild(SceneNodePtr child);
    void removeChild(const SceneNode& child);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;
    void update(const sf::Time& dt);

    void execCommand(const Command& c, const sf::Time& dt);

    sf::Vector2f getWorldPosition() const;
    virtual sf::FloatRect getBoundingBox() const;

    virtual unsigned getCategory() const;

    void getCollisionList(const SceneNode& root, std::set<SceneNodePair> collisionList) const;

protected:
    sf::Transform getWorldTransform() const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(const sf::Time& dt);

    void checkNodeCollisions(const SceneNode& root, std::set<SceneNodePair>& list) const;

    SceneNode*                  parent_ = nullptr;
    std::vector<SceneNodePtr>   children_;
    Category::Type              type_;
};

#endif