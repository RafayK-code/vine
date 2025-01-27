#pragma once

#include <vine/tween/base/AbstractTweenProperty.h>

#include <vine/tween/base/AbstractTweenTarget.h>

namespace vine
{
    class ColorTweenProperty : AbstractTweenProperty
    {
    public:
        ColorTweenProperty(const Color& endValue);
        virtual ~ColorTweenProperty();

        virtual void init(Tween* owner) override;
        virtual void tick(float totalElapsedTime) override;

        virtual void prepareForUse() override;
        virtual AbstractTweenProperty* clone() override;

    private:
        Color startValue_;
        Color endValue_;
        Color diffValue_;

        AbstractTweenTarget* target_;
    };
}