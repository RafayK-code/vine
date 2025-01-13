#include <vine/resource/ResourceManager.h>

#include <vine/core/Logger.h>

namespace vine
{
    ResourceManager::ResourceManager()
    {
    }

    ResourceManager::~ResourceManager()
    {
        for (auto& pair : resources_)
            delete pair.second;
    }

    void ResourceManager::init()
    {
        createSingleton();
    }

    void ResourceManager::shutdown()
    {
        destroySingleton();
    }

    ResourceHandle ResourceManager::addResource(Resource* resource)
    {
        auto it = resources_.find(resource->getHandle());
        if (it != resources_.end())
        {
            DBG_WARN("Resource already exists in manager");
            return resource->getHandle();
        }

        resources_.insert({ resource->getHandle(), resource });
        return resource->getHandle();
    }

    Resource* ResourceManager::getResource(const ResourceHandle& handle)
    {
        auto it = resources_.find(handle);
        if (it == resources_.end())
            return nullptr;

        return it->second;
    }

    void ResourceManager::removeResource(ResourceHandle& handle)
    {
        auto it = resources_.find(handle);
        if (it == resources_.end())
            return;

        delete it->second;
        handle.invalidate();
        resources_.erase(it);
    }
}