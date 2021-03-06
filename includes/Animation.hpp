#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


class Animation : public sf::Drawable, public sf::Transformable
{
public:
    Animation() = default;
    Animation(const sf::Texture& texture, const sf::Vector2i& frameSize, unsigned nbFrames, const sf::Time& duration);
    virtual ~Animation() = default;

    void update(const sf::Time& dt);

    bool isFinished() const { return currentFrame_ >= nbFrames_; }
    const sf::Vector2i& getFrameSize() const { return frameSize_; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite      sprite_;
    sf::Vector2i    frameSize_;
    const unsigned  nbFrames_ = 0;
    unsigned        currentFrame_ = 0;
    const sf::Time  duration_ = sf::Time::Zero;
    sf::Time        elaspedTime_ = sf::Time::Zero;
    bool            repeat = false;
};


#endif