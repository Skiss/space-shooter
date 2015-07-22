#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SceneNode.hpp>

#include <SFML/Graphics.hpp>


class SpriteNode : public SceneNode
{
public:
    SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    unsigned getCategory() const override final;

private:
    sf::Sprite sprite_;
};

#endif