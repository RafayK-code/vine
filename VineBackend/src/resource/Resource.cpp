#include <vine/resource/Resource.h>

namespace vine
{
    ResourceBase::ResourceBase()
        : handle_(xg::Guid()), loaded_(false)
    {
    }

    ResourceBase::~ResourceBase()
    {
    }
}