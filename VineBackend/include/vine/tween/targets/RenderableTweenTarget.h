#pragma once

#include <vine/tween/targets/TweenTarget.h>

#include <vine/renderer/renderable/Renderable.h>

namespace vine
{
    class RenderableTweenTarget : public TweenTarget
    {
    public:
        RenderableTweenTarget(const Ref<Renderable>& target);
        virtual ~RenderableTweenTarget();

        virtual const Vec2& getPosition() const override;
        virtual void setPosition(const Vec2& pos) override;

        virtual const Vec2& getScale() const override;
        virtual void setScale(const Vec2& scale) override;

        virtual float getRotation() const override;
        virtual void setRotation(float rotation) override;

        virtual const Color& getColor() const override;
        virtual void setColor(const Color& color) override;

    private:
        Ref<Renderable> target_;
    };
}