#include <vine/tween/properties/ColorTweenProperty.h>

namespace vine
{
    ColorTweenProperty::ColorTweenProperty(const Color& color)
    {
    }

    ColorTweenProperty::~ColorTweenProperty()
    {
    }

    void ColorTweenProperty::init(Tween* owner)
    {

    }

    void ColorTweenProperty::tick(float totalElapsedTime)
    {

    }

    void ColorTweenProperty::prepareForUse()
    {

    }

    AbstractTweenProperty* ColorTweenProperty::clone()
    {
        return new ColorTweenProperty(*this);
    }
}