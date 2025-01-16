#pragma once

#include <vine/tween/Easing.h>

namespace vine
{
    class Tween;

    class AbstractTweenProperty
    {
    public:
        AbstractTweenProperty();
        virtual ~AbstractTweenProperty();

        virtual void init(Tween* owner);
        virtual void tick(float totalElapsedTime) = 0;

        bool isInitialized() const { return initialized_; }

        void setEaseFunction(easing::EasingFunction easeFunc) { easeFunc_ = easeFunc; }
        easing::EasingFunction getEaseFunction() const { return easeFunc_; }

    protected:
        Tween* owner_;
        bool initialized_;

        easing::EasingFunction easeFunc_;
    };
}