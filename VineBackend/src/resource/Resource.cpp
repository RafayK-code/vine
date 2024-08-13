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

    Resource::Resource(const ResourceCreationData& data)
        : handle_(xg::newGuid()), loaded_(false)
    {
        creationData_ = data.clone();
    }

    Resource::~Resource()
    {
        if (creationData_)
            delete creationData_;
    }
}