#pragma once

#include <vine/resource/ResourceManager.h>

#include <crossguid/guid.hpp>
#include <utility>

namespace vine
{
    using ResourceHandle = xg::Guid;

    class ResourceBase
    {
        friend class ResourceManager;
    public:
        ResourceBase();
        virtual ~ResourceBase();

        const ResourceHandle& getHandle() const { return handle_; }
        bool isLoaded() const { return loaded_; }

    protected:
        ResourceHandle handle_;
        bool loaded_;
    };

    template<typename ResourceType>
    class Resource : public ResourceBase
    {
    public:
        Resource() 
            : resource_(nullptr)
        {
        }

        virtual ~Resource() 
        { 
            if (loaded_)
                delete resource_; 
        }

        template<typename... Args>
        bool load(Args&&... args)
        {
            if (loaded_)
                return false;

            resource_ = new ResourceType(std::forward<Args>(args)...);
            handle_ = xg::newGuid();
            loaded_ = true;
            return true;
        }

        bool unload()
        {
            if (!loaded_)
                return false;

            delete resource_;
            loaded_ = false;
            return true;
        }

        const ResourceType& getResource() const { return *resource_; }

    protected:
        ResourceType* resource_;
    };
}