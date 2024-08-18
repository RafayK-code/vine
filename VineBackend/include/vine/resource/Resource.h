#pragma once

#include <crossguid/guid.hpp>
#include <utility>
#include <string>

namespace vine
{
    using Handle = xg::Guid;

    enum class ResourceDataType
    {
        ResourceDataTypeNone = 0,
        ResourceDataTypeImage,
        ResourceDataTypeFont,
    };

    class ResourceCreationData
    {
    public:
        ResourceCreationData(const std::string& filename);
        ResourceCreationData(const ResourceCreationData& other);

        virtual ~ResourceCreationData();

        virtual ResourceCreationData* clone() const;

        std::string file;
        ResourceDataType type;
    };

    class ResourceManager;

    class Resource
    {
        friend class ResourceManager;
    public:
        virtual ~Resource();

        virtual void load() = 0;
        virtual void unload() = 0;

        const Handle& getHandle() const { return handle_; }
        bool isLoaded() const { return loaded_; }

        const ResourceCreationData* getCreationData() const { return creationData_; }

    protected:
        Resource(const ResourceCreationData& data);

    protected:
        Handle handle_;
        bool loaded_;

        ResourceCreationData* creationData_;
    };
}