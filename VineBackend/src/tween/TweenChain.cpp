#include <vine/tween/TweenChain.h>

namespace vine
{
    TweenChain::TweenChain(const TweenChainConfig& config)
    {
        loopType_ = config.getLoopType();
        iterations_ = config.getIterations();
        state_ = TweenState::Paused;
    }

    TweenChain::~TweenChain()
    {
    }

    void TweenChain::tick(float dt)
    {
        Tweenable::tick(dt);

        float convertedElapsedTime = isLoopingBackOnPingPong_ ? duration_ - elapsedTime_ : elapsedTime_;

        for (auto& item : tweenItems_)
        {
            if (item.getTween() != nullptr && item.getStartTime() < convertedElapsedTime)
            {
                float tweenConvertedElapsed = convertedElapsedTime - item.getStartTime();
                item.getTween()->goTo(tweenConvertedElapsed);
            }
        }

        if (state_ == TweenState::Completed)
        {
            if (!didComplete_)
                onComplete();
        }
    }

    void TweenChain::removeTweenProperty(TweenProperty* property)
    {
        for (auto& item : tweenItems_)
        {
            if (item.getTween() == nullptr)
                continue;

            if (item.getTween()->containsTweenProperty(property))
            {
                item.getTween()->removeTweenProperty(property);
                return;
            }
        }
    }

    bool TweenChain::containsTweenProperty(TweenProperty* property) const
    {
        for (auto& item : tweenItems_)
        {
            if (item.getTween() == nullptr)
                continue;

            if (item.getTween()->containsTweenProperty(property))
                return true;
        }

        return false;
    }

    void TweenChain::getTweenProperties(TweenProperties& list) const
    {
        list.clear();
        for (auto& item : tweenItems_)
        {
            if (item.getTween() == nullptr)
                continue;

            item.getTween()->getTweenProperties(list);
        }
    }

    void TweenChain::complete()
    {
        if (iterations_ < 0)
            return;

        Tweenable::complete();

        for (auto& item : tweenItems_)
        {
            if (item.getTween() != nullptr)
                item.getTween()->goTo(item.getTween()->getTotalDuration());
        }
    }

    void TweenChain::rewind(bool skipDelay)
    {
        state_ = TweenState::Paused;

        elapsedTime_ = 0;
        totalElapsedTime_ = 0;
        isLoopingBackOnPingPong_ = false;
        completedIterations_ = 0;
    }

    TweenChain& TweenChain::append(Tweenable* tween)
    {
        append(TweenChainItem(duration_, tween));
        return *this;
    }

    TweenChain& TweenChain::appendDelay(float delay)
    {
        append(TweenChainItem(0.0f, delay));
        return *this;
    }

    TweenChain& TweenChain::prepend(Tweenable* tween)
    {
        prepend(TweenChainItem(duration_, tween));
        return *this;
    }

    TweenChain& TweenChain::prependDelay(float delay)
    {
        prepend(TweenChainItem(0.0f, delay));
        return *this;
    }

    void TweenChain::append(const TweenChainItem& item)
    {
        tweenItems_.push_back(item);
        duration_ += item.getDuration();

        if (iterations_ >= 0)
            totalDuration_ = duration_ * iterations_;
        else
            totalDuration_ = std::numeric_limits<float>::infinity();
    }

    void TweenChain::prepend(const TweenChainItem& item)
    {
        for (auto& item : tweenItems_)
            item.setStartTime(item.getStartTime() + item.getDuration());

        tweenItems_.insert(tweenItems_.begin(), item);
        duration_ += item.getDuration();

        if (iterations_ >= 0)
            totalDuration_ = duration_ * iterations_;
        else
            totalDuration_ = std::numeric_limits<float>::infinity();
    }
}