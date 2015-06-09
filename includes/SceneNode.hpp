#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>

class SceneNode
{
public:
    typedef std::unique_ptr<SceneNode> SceneNodePtr;

    void addChild(SceneNodePtr child);
    void removeChild(const SceneNode& child);

private:
    SceneNode*                  parent_;
    std::vector<SceneNodePtr>   children_;
};

#endif