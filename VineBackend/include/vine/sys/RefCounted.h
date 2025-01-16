#pragma once

#include <atomic>

namespace vine
{
    class RefCounted
    {
    public:
        RefCounted();
        ~RefCounted();

        uint32_t getRefCount() const { return refCount_; }

    private:
        template <typename T>
        friend class Ref;

        void incRef();
        void decRef();

    private:
        std::atomic<uint32_t> refCount_;
    };
}