#include <vine/sys/RefCounted.h>

#include <vine/core/Logger.h>

namespace vine
{
    RefCounted::RefCounted()
        : refCount_(0)
    {
    }

    RefCounted::~RefCounted()
    {
        DBG_ASSERT(refCount_ == 0, "Ref count somehow is incorrect!");
    }

    RefCounted::RefCounted(const RefCounted& other)
        : refCount_(0)
    {
    }

    RefCounted& RefCounted::operator=(const RefCounted& other)
    {
        // do nothing
        return *this;
    }

    RefCounted::RefCounted(RefCounted&& other) noexcept
        : refCount_(0)
    {
    }

    RefCounted& RefCounted::operator=(RefCounted&& other) noexcept
    {
        // do nothing
        return *this;
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