#include <vine/tween/properties/ColorTweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    ColorTweenProperty::ColorTweenProperty(const Color& endValue)
        : endValue_(endValue), startValue_(Color()), diffValue_(Color()), target_(nullptr)
    {
    }

    ColorTweenProperty::~ColorTweenProperty()
    {
    }

    void ColorTweenProperty::init(Tween* owner)
    {
        if (owner && owner->getTarget())
        {
            target_ = owner->getTarget().get();
            startValue_ = target_->getColor();
        }

        TweenProperty::init(owner);
    }

    void ColorTweenProperty::tick(float totalElapsedTime)
    {
        if (!target_)
            return;

        float easedTime = easeFunc_(totalElapsedTime, 0.0f, 1.0f, owner_->getDuration());
        Color color = Math::unclampedColorLerp(easedTime, startValue_, diffValue_);

        target_->setColor(color);
    }

    void ColorTweenProperty::prepareForUse()
    {
        if (!target_)
            return;

        startValue_ = target_->getColor();
        diffValue_ = endValue_ - startValue_;
    }

    TweenProperty* ColorTweenProperty::clone()
    {
        return new ColorTweenProperty(*this);
    }
}