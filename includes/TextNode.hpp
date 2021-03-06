#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "ResourceIDs.hpp"
#include "SceneNode.hpp"

#include <SFML/Graphics.hpp>


class TextNode : public SceneNode
{
public:
    TextNode(const std::string& text, const FontHolder& fontHolder);

    void setText(const std::string& text);

private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void centerOrigin();

    sf::Text text_;
};

#endif