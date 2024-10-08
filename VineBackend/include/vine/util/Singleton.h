#pragma once

namespace vine
{
    template<typename T>
    class Singleton
    {
    public:
        virtual ~Singleton()
        {
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static void createSingleton()
        {
            getHiddenPtr() = new T();
            getHiddenPtr()->initStatics();
        }

        static void destroySingleton()
        {
            if (!getHiddenPtr())
                return;

            getHiddenPtr()->destroyStatics();
            delete getHiddenPtr();
            getHiddenPtr() = nullptr;
        }

        inline static T* ptr()
        {
            return getHiddenPtr();
        }

        inline static T& ref()
        {
            return *getHiddenPtr();
        }

        virtual void initStatics()
        {
        }

        virtual void destroyStatics()
        {
        }

    protected:
        Singleton()
        {
            getHiddenPtr() = nullptr;
        }

        static inline T*& getHiddenPtr()
        {
            static T* instance_ = nullptr;
            return instance_;
        }
    };

    template<typename T>
    class SingletonStatic
    {
    public:
        static void createSingleton()
        {
        }

        static void destroySingleton()
        {
        }

        inline static T* ptr()
        {
            return &getHiddenPtr();
        }

        inline static T& ref()
        {
            return getHiddenPtr();
        }

    protected:
        SingletonStatic()
        {
        }

        static inline T& getHiddenPtr()
        {
            static T instance_;
            return instance_;
        }
    };
}