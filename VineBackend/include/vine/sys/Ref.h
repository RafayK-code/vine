#pragma once

#include <vine/sys/RefCounted.h>

#include <cstddef>
#include <utility>

namespace vine
{
    // T must be a RefCounted object
    template <typename T>
    class Ref
    {
    public:
        Ref();
        ~Ref();

        Ref(T* ptr);
        Ref<T>& operator=(T* ptr);

        Ref(const Ref<T>& rptr);
        Ref<T>& operator=(const Ref<T>& rptr);

        Ref(Ref<T>&& rptr) noexcept;
        Ref<T>& operator=(Ref<T>&& other) noexcept;

        T* get() { return rcPtr_; }
        T* operator->() { return rcPtr_; }

        const T* get() const { return rcPtr_; }
        const T* operator->() const { return rcPtr_; }

        T& operator*() { return *rcPtr_; }
        const T& operator*() const { return *rcPtr_; }

        bool operator==(const Ref& other) const;
        bool operator==(T* other) const;
        bool operator==(const void* other) const;
        bool operator==(std::nullptr_t) const;

        bool operator!=(const Ref& other) const;
        bool operator!=(T* other) const;
        bool operator!=(const void* other) const;
        bool operator!=(std::nullptr_t) const;

        uint32_t getRefCount() const { return rcPtr_->getRefCount(); }
        bool null() const { return rcPtr_ == nullptr; }

        explicit operator bool() const { return rcPtr_ != nullptr; }

        template <typename T2>
        operator Ref<T2>() { return rcPtr_; }

        template <typename T2>
        operator T2*() { return rcPtr_; }

        template <typename T2>
        operator const T2*() const { return rcPtr_; }

        template <typename T2>
        Ref<T2> dynamicCast() const { return (dynamic_cast<T2*>(rcPtr_)); }

    private:
        void incRef();
        void decRef();

    private:
        T* rcPtr_;
    };

    template <typename T, typename... Args>
    Ref<T> createRef(Args&&... args)
    {
        return Ref<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    Ref<T>::Ref()
        : rcPtr_(nullptr)
    {
    }

    template <typename T>
    Ref<T>::~Ref()
    {
        decRef();
    }

    template <typename T>
    Ref<T>::Ref(T* ptr)
    {
        rcPtr_ = ptr;
        incRef();
    }

    template <typename T>
    Ref<T>& Ref<T>::operator=(T* ptr)
    {
        if (rcPtr_ != ptr)
        {
            decRef();
            rcPtr_ = ptr;
            incRef();
        }

        return *this;
    }

    template <typename T>
    Ref<T>::Ref(const Ref<T>& rptr)
    {
        rcPtr_ = rptr.rcPtr_;
        incRef();
    }

    template <typename T>
    Ref<T>& Ref<T>::operator=(const Ref<T>& rptr)
    {
        if (this != &rptr)
        {
            decRef();
            rcPtr_ = rptr.rcPtr_;
            incRef();
        }

        return *this;
    }

    template <typename T>
    Ref<T>::Ref(Ref<T>&& rptr) noexcept
    {
        rcPtr_ = rptr.rcPtr_;
        rptr.rcPtr_ = nullptr;
    }

    template <typename T>
    Ref<T>& Ref<T>::operator=(Ref<T>&& rptr) noexcept
    {
        if (this != &rptr)
        {
            decRef();
            rcPtr_ = rptr.rcPtr_;
            rptr.rcPtr_ = nullptr;
        }

        return *this;
    }

    template <typename T>
    bool Ref<T>::operator==(const Ref& other) const
    {
        return rcPtr_ == other.rcPtr_;
    }

    template <typename T>
    bool Ref<T>::operator==(T* other) const
    {
        return rcPtr_ == other;
    }

    template <typename T>
    bool Ref<T>::operator==(const void* other) const
    {
        return rcPtr_ == other;
    }

    template <typename T>
    bool Ref<T>::operator==(std::nullptr_t) const
    {
        return rcPtr_ == nullptr;
    }

    template <typename T>
    bool Ref<T>::operator!=(const Ref& other) const
    {
        return rcPtr_ != other.rcPtr_;
    }

    template <typename T>
    bool Ref<T>::operator!=(T* other) const
    {
        return rcPtr_ != other;
    }

    template <typename T>
    bool Ref<T>::operator!=(const void* other) const
    {
        return rcPtr_ != other;
    }

    template <typename T>
    bool Ref<T>::operator!=(std::nullptr_t) const
    {
        return rcPtr_ != nullptr;
    }

    template <typename T>
    void Ref<T>::incRef()
    {
        if (rcPtr_)
            rcPtr_->incRef();
    }

    template <typename T>
    void Ref<T>::decRef()
    {
        if (rcPtr_)
        {
            rcPtr_->decRef();

            if (rcPtr_->getRefCount() == 0)
            {
                delete rcPtr_;
                rcPtr_ = nullptr;
            }
        }
    }
}