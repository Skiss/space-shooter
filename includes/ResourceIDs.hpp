#ifndef RESOURCEIDS_H
#define RESOURCEIDS_H


namespace sf
{
    class Texture;
}

enum class TextureID
{
    Background,
    Eagle
};

template <typename ResourceType, typename Id>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;

#endif