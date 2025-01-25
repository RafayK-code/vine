#include <vine/resource/Resource.h>

#include <vine/resource/ResourceManager.h>

namespace vine
{
    ResourceCreationData::ResourceCreationData(const std::string& filename)
        : file(filename), type(ResourceDataType::ResourceDataTypeNone)
    {
    }

    ResourceCreationData::ResourceCreationData(const ResourceCreationData& other)
        :file(other.file), type(other.type)
    {
    }

    ResourceCreationData::~ResourceCreationData()
    {
    }

    ResourceCreationData* ResourceCreationData::clone() const
    {
        return new ResourceCreationData(*this);
    }

    bool ResourceCreationData::isEqual(const ResourceCreationData& other) const
    {
        return file == other.file;
    }

    bool ResourceCreationData::isLess(const ResourceCreationData& other) const
    {
        return file < other.file;
    }

    bool ResourceCreationData::operator==(const ResourceCreationData& other) const
    {
        return this->isEqual(other);
    }

    bool ResourceCreationData::operator<(const ResourceCreationData& other) const
    {
        return this->isLess(other);
    }

    ResourceHandle::ResourceHandle()
        : guid_(xg::newGuid())
    {
    }

    ResourceHandle::~ResourceHandle()
    {
    }

    bool ResourceHandle::operator<(const ResourceHandle& other) const
    {
        return guid_ < other.guid_;
    }

    bool ResourceHandle::operator==(const ResourceHandle& other) const
    {
        return guid_ == other.guid_;
    }

    Resource::Resource(const ResourceCreationData& data)
        : loaded_(false)
    {
        creationData_ = data.clone();
        ResourceManager::ref().add(this);
    }

    Resource::~Resource()
    {
        ResourceManager::ref().remove(this);

        if (creationData_)
            delete creationData_;
    }
}