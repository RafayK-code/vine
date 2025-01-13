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

        template<typename T, typename CreationT = ResourceCreationData>
        ResourceHandle createResource(const CreationT& data)
        {
            Resource* res = new T(data);
            resources_.insert({ res->getHandle(), res });
            return res->getHandle();
        }

        template<typename T, typename CreationT = ResourceCreationData>
        ResourceHandle createAndLoadResource(const CreationT& data)
        {
            Resource* res = new T(data);
            resources_.insert({ res->getHandle(), res });
            res->load();
            return res->getHandle();
        }

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