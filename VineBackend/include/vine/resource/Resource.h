#pragma once

#include <vine/sys/RefCounted.h>
#include <vine/sys/Ref.h>

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

        virtual bool isEqual(const ResourceCreationData& other) const;
        virtual bool isLess(const ResourceCreationData& other) const;

        bool operator==(const ResourceCreationData& other) const;
        bool operator<(const ResourceCreationData& other) const;

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

    class Resource : public RefCounted
    {
    public:
        Resource(const ResourceCreationData& data);
        virtual ~Resource();

        virtual void reload() = 0;
        virtual void unload() = 0;

        bool isLoaded() const { return loaded_; }

        const std::string& getFile() const { return creationData_->file; }
        const ResourceCreationData* getCreationData() const { return creationData_; }

        const ResourceHandle& getHandle() const { return handle_; }

    protected:
        ResourceHandle handle_;
        bool loaded_;

    private:

        ResourceCreationData* creationData_;
    };
}