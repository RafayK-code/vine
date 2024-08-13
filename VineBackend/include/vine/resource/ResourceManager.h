#pragma once

#include <vine/resource/Resource.h>
#include <vine/util/Singleton.h>
#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/SpriteSheet.h>

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

        template<typename T, typename CreationT>
        const ResourceHandle& createResource(const CreationT& data)
        {
            Resource* res = new T(data);
            
            if (resources_.find(res->getHandle()) != resources_.end())
            {
                delete res;
                return xg::Guid();
            }

            resources_.insert({ res->getHandle(), res });
            return res->getHandle();
        }

        Resource* getResource(const ResourceHandle& handle);
        void removeResource(const ResourceHandle& handle);

    private:
        ResourceManager();

    private:
        std::unordered_map<ResourceHandle, Resource*> resources_;
    };
}