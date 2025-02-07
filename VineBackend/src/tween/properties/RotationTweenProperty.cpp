#include <vine/tween/properties/RotationTweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    RotationTweenProperty::RotationTweenProperty(float endValue)
        : endValue_(endValue), startValue_(0.0f), diffValue_(0.0f), target_(nullptr)
    {
    }

    RotationTweenProperty::~RotationTweenProperty()
    {
    }

    void RotationTweenProperty::init(Tween* owner)
    {
        if (owner && owner->getTarget())
        {
            target_ = owner->getTarget().get();
            startValue_ = target_->getRotation();
        }

        TweenProperty::init(owner);
    }

    void RotationTweenProperty::tick(float totalElapsedTime)
    {
        if (!target_)
            return;

        float easedTime = easeFunc_(totalElapsedTime, 0.0f, 1.0f, owner_->getDuration());
        target_->setRotation(easedTime);
    }

    void RotationTweenProperty::prepareForUse()
    {
        if (!target_)
            return;

        startValue_ = target_->getRotation();
        diffValue_ = endValue_ - startValue_;
    }

    TweenProperty* RotationTweenProperty::clone()
    {
        return new RotationTweenProperty(*this);
    }
}