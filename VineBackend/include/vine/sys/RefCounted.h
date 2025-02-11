#pragma once

#include <atomic>

namespace vine
{
    class RefCounted
    {
    public:
        RefCounted();
        virtual ~RefCounted();

        RefCounted(const RefCounted& other);
        RefCounted& operator=(const RefCounted& other);

        RefCounted(RefCounted&& other) noexcept;
        RefCounted& operator=(RefCounted&& other) noexcept;

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