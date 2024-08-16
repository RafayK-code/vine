#include <vine/resource/ResourceManager.h>

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

    Resource* ResourceManager::getResource(const ResourceHandle& handle)
    {
        auto it = resources_.find(handle);
        if (it == resources_.end())
            return nullptr;

        return it->second;
    }

    void ResourceManager::removeResource(const ResourceHandle& handle)
    {
        auto it = resources_.find(handle);
        if (it == resources_.end())
            return;

        delete it->second;
        resources_.erase(it);
    }
}