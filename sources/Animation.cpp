#include "Animation.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


Animation::Animation(const sf::Texture& texture)
    : sprite_(texture)
{
}

void Animation::update(const sf::Time& dt)
{
    const sf::Time timePerFrame = duration_ / static_cast<float>(nbFrames_);
    elaspedTime_ += dt;

    sf::Vector2i textureBounds(sprite_.getTexture()->getSize());
    sf::IntRect textureRect = sprite_.getTextureRect();

    if (currentFrame_ == 0)
        textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);

    while (elaspedTime_ > timePerFrame && (currentFrame_ < nbFrames_ || repeat))
    {
        elaspedTime_ -= timePerFrame;

        textureRect.left += textureRect.width;

        if (textureRect.left + textureRect.width > textureBounds.x)
        {
            textureRect.left = 0;
            textureRect.top += textureRect.height;
        }

        if (repeat)
        {
            currentFrame_ = (currentFrame_ + 1) % nbFrames_;

            if (currentFrame_ == 0)
                textureRect = sf::IntRect(0, 0, frameSize_.x, frameSize_.y);
        }
        else
            ++currentFrame_;
    }

    sprite_.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite_, states);
}
