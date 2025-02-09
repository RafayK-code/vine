#include <vine/tween/TweenChainItem.h>

namespace vine
{
    TweenChainItem::TweenChainItem(float startTime, Tweenable* tween)
        : tween_(tween), startTime_(startTime)
    {
        duration_ = tween->getDuration();
    }

    TweenChainItem::TweenChainItem(float startTime, float duration)
        : tween_(nullptr), startTime_(startTime), duration_(duration)
    {
    }
}