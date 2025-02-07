#pragma once

#include <vine/sys/Ref.h>
#include <vine/util/Math.h>

namespace vine
{
    class TweenTarget : public RefCounted
    {
    public:
        virtual ~TweenTarget() = default;

        virtual const Vec2& getPosition() const = 0;
        virtual void setPosition(const Vec2& pos) = 0;

        virtual const Vec2& getScale() const = 0;
        virtual void setScale(const Vec2& scale) = 0;

        virtual float getRotation() const = 0;
        virtual void setRotation(float rotation) = 0;

        virtual const Color& getColor() const = 0;
        virtual void setColor(const Color& color) = 0;
    };
}