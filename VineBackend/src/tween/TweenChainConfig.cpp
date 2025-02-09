#include <vine/tween/TweenChainConfig.h>

namespace vine
{
    TweenChainConfig::TweenChainConfig()
        : iterations_(1), loopType_(TweenLoopType::Restart)
    {
    }

    TweenChainConfig::~TweenChainConfig()
    {
    }

    TweenChainConfig& TweenChainConfig::setIterations(int iterations)
    {
        iterations_ = iterations;
        return *this;
    }

    TweenChainConfig& TweenChainConfig::setLoopType(TweenLoopType loopType)
    {
        loopType_ = loopType;
        return *this;
    }
}