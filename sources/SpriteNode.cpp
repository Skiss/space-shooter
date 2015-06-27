#include "SpriteNode.hpp"


SpriteNode::SpriteNode(const sf::Texture& texture)
    : sprite_(texture)
{

}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}
