#include <vine/tween/properties/ScaleTweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    ScaleTweenProperty::ScaleTweenProperty(const Vec2& endValue)
        : endValue_(endValue), startValue_(Vec2()), diffValue_(Vec2()), target_(nullptr)
    {
    }

    ScaleTweenProperty::~ScaleTweenProperty()
    {
    }

    void ScaleTweenProperty::init(Tween* owner)
    {
        if (owner && owner->getTarget())
        {
            target_ = owner->getTarget().get();
            startValue_ = target_->getColor();
        }

        TweenProperty::init(owner);
    }

    void ScaleTweenProperty::tick(float totalElapsedTime)
    {
        if (!target_)
            return;

        float easedTime = easeFunc_(totalElapsedTime, 0.0f, 1.0f, owner_->getDuration());
        Vec2 scale = Math::unclampedVec2Lerp(easedTime, startValue_, diffValue_);

        target_->setPosition(scale);
    }

    void ScaleTweenProperty::prepareForUse()
    {
        if (!target_)
            return;

        startValue_ = target_->getPosition();
        diffValue_ = endValue_ - startValue_;
    }

    TweenProperty* ScaleTweenProperty::clone()
    {
        return new ScaleTweenProperty(*this);
    }
}