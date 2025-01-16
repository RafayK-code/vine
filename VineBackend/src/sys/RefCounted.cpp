#include <vine/sys/RefCounted.h>

namespace vine
{
    RefCounted::RefCounted()
        : refCount_(0)
    {
    }

    RefCounted::~RefCounted()
    {
    }

    void RefCounted::incRef()
    {
        refCount_++;
    }

    void RefCounted::decRef()
    {
        refCount_--;
    }
}