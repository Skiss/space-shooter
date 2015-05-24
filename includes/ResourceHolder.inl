#include "ResourceHolder.hpp"

#include <cassert>


template <typename ResourceType, typename ID>
void ResourceHolder<ResourceType, ID>::load(ID id, const std::string& path)
{
    auto resource = std::make_unique<ResourceType>();

    if (!resource->loadFromFile(path))
        throw std::runtime_error("Could not load resource at this location: " + path);

    auto res = resourceMap_.insert(std::make_pair(id, std::move(resource)));

    assert(res.second);
}

template <typename ResourceType, typename ID>
const ResourceType& ResourceHolder<ResourceType, ID>::get(ID id) const
{
    auto res = resourceMap_.find(id);
    assert(res != end(resourceMap_));

    return *res->second;
}

template <typename ResourceType, typename ID>
ResourceType& ResourceHolder<ResourceType, ID>::get(ID id)
{
    auto res = resourceMap_.find(id);
    assert(res != end(resourceMap_));

    return *res->second;
}
