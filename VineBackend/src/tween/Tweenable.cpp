#include <vine/tween/Tweenable.h>

#include <vine/util/Math.h>

namespace vine
{
    Tweenable::Tweenable()
        : didStart_(false)
        , didComplete_(false)
        , elapsedTime_(0.0f)
        , totalElapsedTime_(0.0f)
        , duration_(0.0f)
        , totalDuration_(0.0f)
        , completedIterations_(0)
    {
    }

    Tweenable::~Tweenable()
    {
    }

    void Tweenable::onStart()
    {
        didStart_ = true;
    }

    void Tweenable::onComplete()
    {
        didComplete_ = true;
    }

    void Tweenable::tick(float dt)
    {
        if (!didStart_)
            onStart();

        totalElapsedTime_ += dt;
        totalElapsedTime_ = Math::clamp(totalElapsedTime_, 0.0f, totalDuration_);

        completedIterations_ = static_cast<int>(Math::floor(totalElapsedTime_ / duration_));

        isLoopingBackOnPingPong_ = false;
        if (loopType_ == TweenLoopType::PingPong)
        {
            if (iterations_ < 0 && completedIterations_ % 2 != 0)
                isLoopingBackOnPingPong_ = true;
            else if (iterations_ > 0)
            {
                if (completedIterations_ >= iterations_ && completedIterations_ % 2 == 0)
                    isLoopingBackOnPingPong_ = true;
                else if (completedIterations_ < iterations_ && completedIterations_ % 2 != 0)
                    isLoopingBackOnPingPong_ = true;
            }
        }

        if (iterations_ > 0 && completedIterations_ >= iterations_)
        {
            elapsedTime_ = duration_;

            state_ = TweenState::Completed;
        }
        else if (totalElapsedTime_ < duration_)
        {
            elapsedTime_ = totalElapsedTime_;
        }
        else
        {
            elapsedTime_ = std::fmod(totalElapsedTime_, duration_);
        }
    }

    void Tweenable::destroy()
    {
        state_ = TweenState::Destroyed;
    }

    void Tweenable::complete()
    {
        if (iterations_ < 0)
            return;

        elapsedTime_ = 0;
        totalElapsedTime_ = 0;
        completedIterations_ = 0;
        state_ = TweenState::Running;
    }

    void Tweenable::restart(bool skipDelay)
    {
        didComplete_ = false;
        rewind(skipDelay);
        state_ = TweenState::Running;
    }
}