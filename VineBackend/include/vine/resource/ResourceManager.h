#pragma once

#include <vine/resource/Resource.h>
#include <vine/util/Singleton.h>
#include <vine/renderer/renderable/Sprite.h>

#include <unordered_map>

namespace vine
{
    class ResourceManager : public Singleton<ResourceManager>
    {
        friend class Singleton<ResourceManager>;
    public:
        ~ResourceManager();

        static void init();
        static void shutdown();

        Handle addResource(Resource* resource);

        template<typename T, typename CreationT = ResourceCreationData>
        Handle createResource(const CreationT& data)
        {
            Resource* res = new T(data);
            resources_.insert({ res->getHandle(), res });
            return res->getHandle();
        }

        template<typename T, typename CreationT = ResourceCreationData>
        Handle createAndLoadResource(const CreationT& data)
        {
            Resource* res = new T(data);
            resources_.insert({ res->getHandle(), res });
            res->load();
            return res->getHandle();
        }

        Resource* getResource(const Handle& handle);

        template<typename T>
        T* getResource(const Handle& handle)
        {
            return dynamic_cast<T*>(getResource(handle));
        }

        void removeResource(const Handle& handle);

    private:
        ResourceManager();

    private:
        std::unordered_map<Handle, Resource*> resources_;
    };
}