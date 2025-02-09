#include <vine/tween/TweenConfig.h>

#include <vine/tween/properties/ColorTweenProperty.h>
#include <vine/tween/properties/PositionTweenProperty.h>
#include <vine/tween/properties/RotationTweenProperty.h>
#include <vine/tween/properties/ScaleTweenProperty.h>

namespace vine
{
    TweenConfig::TweenConfig()
        : iterations_(1), delay_(0), loopType_(TweenLoopType::Restart), easeFunc_(easing::Linear::easeNone)
    {
    }

    TweenConfig::~TweenConfig()
    {
    }

    TweenConfig& TweenConfig::position(const Vec2& endValue)
    {
        PositionTweenProperty* property = new PositionTweenProperty(endValue);
        properties_.push_back(property);

        return *this;
    }

    TweenConfig& TweenConfig::scale(const Vec2& endValue)
    {
        ScaleTweenProperty* property = new ScaleTweenProperty(endValue);
        properties_.push_back(property);

        return *this;
    }

    TweenConfig& TweenConfig::rotation(float endValue)
    {
        RotationTweenProperty* property = new RotationTweenProperty(endValue);
        properties_.push_back(property);

        return *this;
    }

    TweenConfig& TweenConfig::color(const Color& endValue)
    {
        ColorTweenProperty* property = new ColorTweenProperty(endValue);
        properties_.push_back(property);

        return *this;
    }

    TweenConfig& TweenConfig::setIterations(int iterations)
    {
        iterations_ = iterations;
        return *this;
    }

    TweenConfig& TweenConfig::setDelay(float delay)
    {
        delay_ = delay;
        return *this;
    }

    TweenConfig& TweenConfig::setLoopType(TweenLoopType loopType)
    {
        loopType_ = loopType;
        return *this;
    }

    TweenConfig& TweenConfig::setTweenState(TweenState state)
    {
        state_ = state;
        return *this;
    }

    TweenConfig& TweenConfig::setEase(easing::EasingFunction ease)
    {
        easeFunc_ = ease;
        return *this;
    }

}