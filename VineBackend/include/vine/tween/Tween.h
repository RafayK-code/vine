#include <vine/tween/base/AbstractTween.h>

#include <vine/tween/base/AbstractTweenTarget.h>
#include <vine/tween/Easing.h>

namespace vine
{
    class Tween : public AbstractTween
    {
    public:
        Tween();
        virtual ~Tween();

        easing::EasingFunction getEaseFunction() const { return easeFunc_; }
        bool isFrom() const { return isFrom_; }
    private:
        Ref<AbstractTweenTarget> target_;

        bool isFrom_;

        easing::EasingFunction easeFunc_;
    };
}