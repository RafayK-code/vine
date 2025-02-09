#pragma once

#include <vine/tween/properties/TweenProperty.h>

#include <vine/tween/targets/TweenTarget.h>

namespace vine
{
    class RotationTweenProperty : public TweenProperty
    {
    public:
        RotationTweenProperty(float endValue);
        virtual ~RotationTweenProperty();

        virtual void init(Tween* owner) override;
        virtual void tick(float totalElapsedTime) override;

        virtual void prepareForUse() override;
        virtual TweenProperty* clone() override;

    private:
        float startValue_;
        float endValue_;
        float diffValue_;

        TweenTarget* target_;
    };
}