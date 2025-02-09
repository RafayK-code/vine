#pragma once

#include <vine/tween/Tweenable.h>

namespace vine
{
    class TweenChainItem
    {
    public:
        TweenChainItem(float startTime, Tweenable* tween);
        TweenChainItem(float startTime, float duration);

        float getStartTime() const { return startTime_; }
        void setStartTime(float startTime) { startTime_ = startTime; }

        float getDuration() const { return duration_; }
        void setDuration(float duration) { duration_ = duration; }

        const Ref<Tweenable>& getTween() const { return tween_; }
        Ref<Tweenable> getTween() { return tween_; }
        void setTween(const Ref<Tweenable>& tween) { tween_ = tween; }

    private:

        float startTime_;
        float duration_;
        Ref<Tweenable> tween_;
    };
}