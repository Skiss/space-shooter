#ifndef RESOURCEIDS_H
#define RESOURCEIDS_H


namespace sf
{
    class Font;
    class Texture;
}

enum class TextureID
{
    Background,
    Entities,
    TitleScreen,
    Particle,
    Explosion
};

enum class FontID
{
    Sensation
};

template <typename ResourceType, typename Id>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;

typedef ResourceHolder<sf::Font, FontID> FontHolder;

#endif