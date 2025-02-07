#include <vine/tween/properties/PositionTweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    PositionTweenProperty::PositionTweenProperty(const Vec2& endValue)
        : endValue_(endValue), startValue_(Vec2()), diffValue_(Vec2()), target_(nullptr)
    {
    }

    PositionTweenProperty::~PositionTweenProperty()
    {
    }

    void PositionTweenProperty::init(Tween* owner)
    {
        if (owner && owner->getTarget())
        {
            target_ = owner->getTarget().get();
            startValue_ = target_->getColor();
        }

        TweenProperty::init(owner);
    }

    void PositionTweenProperty::tick(float totalElapsedTime)
    {
        if (!target_)
            return;

        float easedTime = easeFunc_(totalElapsedTime, 0.0f, 1.0f, owner_->getDuration());
        Vec2 pos = Math::unclampedVec2Lerp(easedTime, startValue_, diffValue_);

        target_->setPosition(pos);
    }

    void PositionTweenProperty::prepareForUse()
    {
        if (!target_)
            return;

        startValue_ = target_->getPosition();
        diffValue_ = endValue_ - startValue_;
    }

    TweenProperty* PositionTweenProperty::clone()
    {
        return new PositionTweenProperty(*this);
    }
}