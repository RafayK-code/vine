#pragma once

#include <vine/tween/properties/TweenProperty.h>

#include <vine/tween/targets/TweenTarget.h>

namespace vine
{
    class PositionTweenProperty : public TweenProperty
    {
    public:
        PositionTweenProperty(const Vec2& endValue);
        virtual ~PositionTweenProperty();

        virtual void init(Tween* owner) override;
        virtual void tick(float totalElapsedTime) override;

        virtual void prepareForUse() override;
        virtual TweenProperty* clone() override;

    private:
        Vec2 startValue_;
        Vec2 endValue_;
        Vec2 diffValue_;

        TweenTarget* target_;
    };
}