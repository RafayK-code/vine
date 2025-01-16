#include <vine/tween/base/AbstractTweenProperty.h>

#include <vine/tween/Tween.h>

namespace vine
{
    AbstractTweenProperty::AbstractTweenProperty()
        : owner_(nullptr), initialized_(false), easeFunc_(nullptr)
    {
    }

    AbstractTweenProperty::~AbstractTweenProperty()
    {
    }

    void AbstractTweenProperty::init(Tween* owner)
    {
        owner_ = owner;
        initialized_ = true;

        if (!easeFunc_)
            easeFunc_ = owner_->getEaseFunction();
    }
}