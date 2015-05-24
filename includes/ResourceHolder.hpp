#ifndef RESOURCESHOLDER_H
#define RESOURCESHOLDER_H

#include <memory>
#include <unordered_map>


template <typename ResourceType, typename ID>
class ResourceHolder
{
public:
    void load(ID id, const std::string& path);

    ResourceType& get(ID id);
    const ResourceType& get(ID id) const;

private:
    std::unordered_map<ID, std::unique_ptr<ResourceType>> resourceMap_;
};

#include "ResourceHolder.inl"


#endif