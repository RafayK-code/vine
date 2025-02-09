#pragma once

#include <vine/tween/TweenConfig.h>

#include <functional>

namespace vine
{
    class Tweenable : public RefCounted
    {
    public:
        Tweenable();
        virtual ~Tweenable();

        virtual void tick(float dt);

        void play() { state_ = TweenState::Running; }
        void pause() { state_ = TweenState::Paused; }

        virtual void complete();
        virtual void destroy();
        virtual void rewind(bool skipDelay = true) = 0;

        void restart(bool skipDelay = true);

        virtual void goTo(float time);

        virtual void removeTweenProperty(TweenProperty* property) = 0;
        virtual bool containsTweenProperty(TweenProperty* property) const = 0;
        virtual void getTweenProperties(TweenProperties& list) const = 0;

        void setOnStartHandler(std::function<void()> onStart) { onStart_ = onStart; }
        void setOnTickHandler(std::function<void()> onTick) { onTick_ = onTick; }
        void setOnDoneHandler(std::function<void()> onComplete) { onComplete_ = onComplete; }

        float getDuration() const { return duration_; }
        float getTotalDuration() const { return totalDuration_; }

        TweenState getState() const { return state_; }
        TweenLoopType getLoopType() const { return loopType_; }

        int getIterations() const { return iterations_; }
        int getCompletedIterations() const { return iterations_; }

        bool isLoopingBackOnPingPong() const { return isLoopingBackOnPingPong_; }

    protected:
        virtual void onStart();
        virtual void onComplete();

    protected:
        float duration_;
        float totalDuration_;

        TweenState state_;
        TweenLoopType loopType_;

        int iterations_;
        int completedIterations_;

        float elapsedTime_;
        float totalElapsedTime_;

        bool isLoopingBackOnPingPong_;
        bool didStart_;
        bool didComplete_;

        std::function<void()> onStart_;
        std::function<void()> onTick_;
        std::function<void()> onComplete_;
    };
}