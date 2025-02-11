#include <vine/tween/targets/CameraTweenTarget.h>

namespace vine
{
    static Color defaultColor;

    CameraTweenTarget::CameraTweenTarget(OrthographicCamera& target)
        : target_(target)
    {
    }

    CameraTweenTarget::~CameraTweenTarget()
    {
    }

    const Vec2& CameraTweenTarget::getPosition() const
    {
        return pos_;
    }

    void CameraTweenTarget::setPosition(const Vec2& pos)
    {
    }

    const Vec2& CameraTweenTarget::getScale() const
    {
        return scale_;
    }

    void CameraTweenTarget::setScale(const Vec2& scale)
    {
    }

    float CameraTweenTarget::getRotation() const
    {
        return rotation_;
    }

    void CameraTweenTarget::setRotation(float rotation)
    {
    }

    const Color& CameraTweenTarget::getColor() const
    {
        return defaultColor;
    }

    void CameraTweenTarget::setColor(const Color& color)
    {
    }
}