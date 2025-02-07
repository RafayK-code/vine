#include <vine/tween/targets/RenderableTweenTarget.h>

namespace vine
{
    RenderableTweenTarget::RenderableTweenTarget(const Ref<Renderable>& target)
        : target_(target)
    {
    }

    RenderableTweenTarget::~RenderableTweenTarget()
    {
    }

    const Vec2& RenderableTweenTarget::getPosition() const
    {
        return target_->getPosition();
    }

    void RenderableTweenTarget::setPosition(const Vec2& pos)
    {
        target_->setPosition(pos);
    }

    const Vec2& RenderableTweenTarget::getScale() const
    {
        return target_->getScale();
    }

    void RenderableTweenTarget::setScale(const Vec2& scale)
    {
        target_->setScale(scale);
    }

    float RenderableTweenTarget::getRotation() const
    {
        return target_->getRotation();
    }

    void RenderableTweenTarget::setRotation(float rotation)
    {
        target_->setRotation(rotation);
    }

    const Color& RenderableTweenTarget::getColor() const
    {
        return target_->getColor();
    }

    void RenderableTweenTarget::setColor(const Color& color)
    {
        target_->setColor(color);
    }


}