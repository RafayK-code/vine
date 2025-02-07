#pragma once

#include <vine/tween/properties/TweenProperty.h>

#include <vine/tween/targets/TweenTarget.h>

namespace vine
{
    class ColorTweenProperty : public TweenProperty
    {
    public:
        ColorTweenProperty(const Color& endValue);
        virtual ~ColorTweenProperty();

        virtual void init(Tween* owner) override;
        virtual void tick(float totalElapsedTime) override;

        virtual void prepareForUse() override;
        virtual TweenProperty* clone() override;

    private:
        Color startValue_;
        Color endValue_;
        Color diffValue_;

        TweenTarget* target_;
    };
}