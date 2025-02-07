#pragma once

#include <vine/tween/Tweenable.h>

#include <vine/tween/targets/TweenTarget.h>
#include <vine/tween/Easing.h>

namespace vine
{
    class Tween : public Tweenable
    {
    public:
        Tween(TweenTarget* target, float duration, const TweenConfig& config);
        virtual ~Tween();

        virtual void tick(float dt);

        virtual void complete() override;
        virtual void destroy() override;
        virtual void rewind(bool skipDelay = true) override;

        virtual void addTweenProperty(TweenProperty* propetry);
        virtual void removeTweenProperty(TweenProperty* property) override;
        virtual bool containsTweenProperty(TweenProperty* property) const override;

        virtual const TweenProperties& getTweenProperties() const override;
        void clearTweenProperties();

        Ref<TweenTarget> getTarget() { return target_; }

        float getDelay() const { return delay_; }
        bool delayComplete() const { return delayComplete_; }

        easing::EasingFunction getEaseFunction() const { return easeFunc_; }
        void setEaseFunction(easing::EasingFunction func);

    protected:
        virtual void onStart() override;

    private:
        Ref<TweenTarget> target_;

        float delay_;
        float elapsedDelay_;
        bool delayComplete_;

        TweenProperties properties_;

        easing::EasingFunction easeFunc_;
    };
}