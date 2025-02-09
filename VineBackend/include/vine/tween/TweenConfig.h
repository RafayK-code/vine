#pragma once

#include <vine/tween/properties/TweenProperty.h>
#include <vine/tween/TweenEnums.h>

#include <vine/util/Math.h>

namespace vine
{
    using TweenProperties = std::vector<Ref<TweenProperty>>;

    class TweenConfig
    {
    public:
        TweenConfig();
        ~TweenConfig();

        TweenConfig& position(const Vec2& endValue);
        TweenConfig& scale(const Vec2& endValue);
        TweenConfig& rotation(float endValue);
        TweenConfig& color(const Color& endValue);

        TweenConfig& setIterations(int iterations);
        TweenConfig& setDelay(float delay);
        TweenConfig& setLoopType(TweenLoopType loop);
        TweenConfig& setTweenState(TweenState state);

        TweenConfig& setEase(easing::EasingFunction ease);

        const TweenProperties& getProperties() const { return properties_; }

        int getIterations() const { return iterations_; }
        float getDelay() const { return delay_; }

        TweenLoopType getLoopType() const { return loopType_; }
        TweenState getTweenState() const { return state_; }

        easing::EasingFunction getEaseFunction() const { return easeFunc_; }

    private:
        easing::EasingFunction easeFunc_;
        TweenProperties properties_;

        float delay_;
        int iterations_;
        TweenLoopType loopType_;
        TweenState state_;
    };
}