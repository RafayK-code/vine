#pragma once

#include <vine/util/Singleton.h>

namespace vine
{
    class TweenManager : public Singleton<TweenManager>
    {
        friend class Singleton<TweenManager>;
    public:
        ~TweenManager() {}

        void init() {}
        void shutdown() {}

    private:
        TweenManager() {}
    };
}