#include <vine/tween/base/AbstractTween.h>

#include <vine/tween/Easing.h>

namespace vine
{
    class Tween : public AbstractTween
    {
    public:
        easing::EasingFunction getEaseFunction() const { return easeFunc_; }
    private:
        easing::EasingFunction easeFunc_;
    };
}