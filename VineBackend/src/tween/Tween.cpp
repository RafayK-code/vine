#include <vine/tween/Tween.h>

namespace vine
{
    Tween::Tween(TweenTarget* target, float duration, const TweenConfig& config)
        : target_(target)
    {
        duration_ = duration;

        elapsedDelay_ = 0.0f;
        delayComplete_ = false;

        delay_ = config.getDelay();
        loopType_ = config.getLoopType();
        iterations_ = config.getIterations();
        easeFunc_ = config.getEaseFunction();
        state_ = config.getTweenState();

        const TweenProperties& configProperties = config.getProperties();

        for (int i = 0; i < configProperties.size(); i++)
        {
            Ref<TweenProperty> prop = configProperties[i];
            if (prop->isInitialized())
                prop = prop->clone();

            addTweenProperty(prop);
        }

        if (iterations_ < 0)
            totalDuration_ = std::numeric_limits<float>::infinity();
        else
            totalDuration_ = iterations_ * duration_;
    }

    Tween::~Tween()
    {
    }

    void Tween::tick(float dt)
    {
        if (!delayComplete_ && elapsedDelay_ < delay_)
        {
            elapsedDelay_ += dt;

            if (elapsedDelay_ >= delay_)
                delayComplete_ = true;

            // start tween on next tick
            return;
        }

        Tweenable::tick(dt);

        float convertedElapsedTime = isLoopingBackOnPingPong_ ? duration_ - elapsedTime_ : elapsedTime_;

        for (auto& prop : properties_)
            prop->tick(convertedElapsedTime);

        if (state_ == TweenState::Completed)
        {
            if (!didComplete_)
                onComplete();
        }
    }

    void Tween::addTweenProperty(TweenProperty* property)
    {
        properties_.push_back(property);
        property->init(this);
    }

    void Tween::removeTweenProperty(TweenProperty* property)
    {
        auto itr = std::find(properties_.begin(), properties_.end(), property);
        if (itr != properties_.end())
            properties_.erase(itr);
    }

    bool Tween::containsTweenProperty(TweenProperty* property) const
    {
        auto itr = std::find(properties_.begin(), properties_.end(), property);
        return itr != properties_.end();
    }

    void Tween::getTweenProperties(TweenProperties& list) const
    {
        list.insert(list.end(), properties_.begin(), properties_.end());
    }

    void Tween::clearTweenProperties()
    {
        properties_.clear();
    }

    void Tween::complete()
    {
        if (iterations_ < 0)
            return;

        Tweenable::complete();
        delayComplete_ = true;
    }

    void Tween::destroy()
    {
        target_ = nullptr;
        properties_.clear();
        Tweenable::destroy();
    }

    void Tween::rewind(bool skipDelay)
    {
        state_ = TweenState::Paused;

        elapsedTime_ = 0.0f;
        totalElapsedTime_ = 0.0f;
        elapsedDelay_ = skipDelay ? duration_ : 0.0f;
        delayComplete_ = skipDelay;
        isLoopingBackOnPingPong_ = false;
        completedIterations_ = 0;
    }

    void Tween::goTo(float time)
    {
        delayComplete_ = true;
        elapsedDelay_ = delay_;

        Tweenable::goTo(time);
    }

    void Tween::onStart()
    {
        Tweenable::onStart();

        for (auto& prop : properties_)
            prop->prepareForUse();
    }

    void Tween::setEaseFunction(easing::EasingFunction func)
    {
        easeFunc_ = func;
        for (auto& prop : properties_)
            prop->setEaseFunction(func);
    }
}