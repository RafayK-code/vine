#pragma once

#include <vine/tween/targets/TweenTarget.h>

#include <vine/renderer/OrthographicCamera.h>

namespace vine
{
    class CameraTweenTarget : public TweenTarget
    {
    public:
        CameraTweenTarget(OrthographicCamera& target);
        virtual ~CameraTweenTarget();

        virtual const Vec2& getPosition() const override;
        virtual void setPosition(const Vec2& pos) override;

        virtual const Vec2& getScale() const override;
        virtual void setScale(const Vec2& scale) override;

        virtual float getRotation() const override;
        virtual void setRotation(float rotation) override;

        virtual const Color& getColor() const override;
        virtual void setColor(const Color& color) override;

    private:
        OrthographicCamera& target_;

        Vec2 pos_;
        Vec2 scale_;
        float rotation_;
    };
}