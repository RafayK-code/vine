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

    Resource* ResourceManager::get(const ResourceCreationData& filename)
    {
        auto it = resources_.find(&filename);

        while (it != resources_.end())
        {
            if (it->first->isEqual(filename))
                return it->second;

            it++;
        }

        return nullptr;
    }

    void ResourceManager::add(Resource* resource)
    {
        Resource* res = get(*resource->getCreationData());
        if (res != nullptr)
            return;

        resources_.insert({ resource->getCreationData(), resource });
    }

    void ResourceManager::remove(Resource* resource)
    {
        auto it = resources_.find(resource->getCreationData());

        while (it != resources_.end())
        {
            if (it->first->isEqual(*resource->getCreationData()))
            {
                resources_.erase(it);
                break;
            }

            it++;
        }
    }
}