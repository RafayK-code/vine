#pragma once

#include <crossguid/guid.hpp>
#include <utility>
#include <string>

namespace vine
{
    //using Handle = xg::Guid;

    enum class ResourceDataType
    {
        ResourceDataTypeNone = 0,
        ResourceDataTypeImage,
        ResourceDataTypeFont,
        ResourceDataTypeScript,
    };

    class ResourceCreationData
    {
    public:
        ResourceCreationData(const std::string& filename);
        ResourceCreationData(const ResourceCreationData& other);

        virtual ~ResourceCreationData();

        virtual ResourceCreationData* clone() const;

        virtual bool operator<(const ResourceCreationData& other) const;

        std::string file;
        ResourceDataType type;
    };

    class ResourceHandle
    {
    public:
        ResourceHandle();
        ~ResourceHandle();

        bool isValid() const { return guid_.isValid(); }
        void invalidate() { guid_ = xg::Guid(); }

        bool operator<(const ResourceHandle& other) const;
        bool operator==(const ResourceHandle& other) const;

    private:
        xg::Guid guid_;
    };

    class ResourceManager;

    class Resource
    {
    public:
        virtual ~Resource();

        virtual void load() = 0;
        virtual void unload() = 0;

        bool isLoaded() const { return loaded_; }

        const ResourceCreationData* getCreationData() const { return creationData_; }
        const ResourceHandle& getHandle() const { return handle_; }

    protected:
        Resource(const ResourceCreationData& data);

    protected:
        bool loaded_;
        ResourceHandle handle_;

        ResourceCreationData* creationData_;
    };
}