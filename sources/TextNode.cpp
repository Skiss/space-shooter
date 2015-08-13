#include "TextNode.hpp"

#include "ResourceHolder.hpp"


TextNode::TextNode(const std::string& text, const FontHolder& fontHolder)
    : text_(text, fontHolder.get(FontID::Sensation), 18)
{
    centerOrigin();
}

void TextNode::setText(const std::string& text)
{
    text_.setString(text);
    centerOrigin();
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text_, states);
}

void TextNode::centerOrigin()
{
    text_.setOrigin(text_.getLocalBounds().width / 2.f, text_.getLocalBounds().height / 2.f);
}
