#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SceneNode.hpp>

#include <SFML/Graphics.hpp>


class SpriteNode : public SceneNode
{
public:
    SpriteNode(const sf::Texture& texture);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite_;
};

#endif