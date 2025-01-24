#pragma once

#include <vine/resource/Resource.h>
#include <vine/util/Singleton.h>

#include <map>

namespace vine
{
    class ResourceManager : public Singleton<ResourceManager>
    {
        friend class Singleton<ResourceManager>;
    public:
        ~ResourceManager();

        static void init();
        static void shutdown();

        ResourceHandle addResource(Resource* resource);

        Resource* getResource(const ResourceHandle& handle);

        template<typename T>
        T* getResource(const ResourceHandle& handle)
        {
            return dynamic_cast<T*>(getResource(handle));
        }

        void removeResource(ResourceHandle& handle);

    private:
        ResourceManager();

    private:
        std::map<ResourceHandle, Resource*> resources_;
    };
}