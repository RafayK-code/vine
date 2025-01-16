#pragma once

#include <vine/tween/base/AbstractTweenProperty.h>

#include <vine/util/Math.h>

namespace vine
{
    class ColorTweenProperty : AbstractTweenProperty
    {
    public:
        ColorTweenProperty(const Color& endValue);
        virtual ~ColorTweenProperty();

        virtual void init(Tween* owner) override;
        virtual void tick(float totalElapsedTime) override;

    private:
        Color startValue_;
        Color endValue_;
        Color diffValue_;
    };
}