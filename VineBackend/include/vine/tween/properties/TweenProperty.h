#pragma once

#include <vine/tween/Easing.h>
#include <vine/sys/Ref.h>

namespace vine
{
    class Tween;

    class TweenProperty : public RefCounted
    {
    public:
        TweenProperty();
        virtual ~TweenProperty();

        virtual void init(Tween* owner);
        virtual void tick(float totalElapsedTime) = 0;

        bool isInitialized() const { return initialized_; }

        void setEaseFunction(easing::EasingFunction easeFunc) { easeFunc_ = easeFunc; }
        easing::EasingFunction getEaseFunction() const { return easeFunc_; }

        virtual void prepareForUse() = 0;
        virtual TweenProperty* clone() = 0;

    protected:
        Tween* owner_;
        bool initialized_;

        easing::EasingFunction easeFunc_;
    };
}