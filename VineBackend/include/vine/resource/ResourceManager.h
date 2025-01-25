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

        Resource* get(const ResourceCreationData& filename);

        void add(Resource* resource);
        void remove(Resource* resource);

    private:
        ResourceManager();

    private:
        class ResourceCreationCompare
        {
        public:
            bool operator()(const ResourceCreationData* lhs, const ResourceCreationData* rhs) const
            {
                return lhs->isLess(*rhs);
            }
        };

        using ResourceMap = std::map<const ResourceCreationData*, Resource*, ResourceCreationCompare>;
        ResourceMap resources_;
    };
}