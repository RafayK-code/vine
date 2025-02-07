#include <vine/tween/properties/TweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    TweenProperty::TweenProperty()
        : owner_(nullptr), initialized_(false), easeFunc_(nullptr)
    {
    }

    TweenProperty::~TweenProperty()
    {
    }

    void TweenProperty::init(Tween* owner)
    {
        owner_ = owner;
        initialized_ = true;

        if (!easeFunc_)
            easeFunc_ = owner_->getEaseFunction();
    }
}