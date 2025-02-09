#pragma once

#include <vine/tween/TweenEnums.h>

namespace vine
{
    class TweenChainConfig
    {
    public:
        TweenChainConfig();
        ~TweenChainConfig();

        TweenChainConfig& setIterations(int iterations);
        TweenChainConfig& setLoopType(TweenLoopType loopType);

        int getIterations() const { return iterations_; }
        TweenLoopType getLoopType() const { return loopType_; }

    private:
        int iterations_;
        TweenLoopType loopType_;
    };
}