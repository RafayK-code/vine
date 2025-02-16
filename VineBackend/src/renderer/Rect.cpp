#include <vine/renderer/Rect.h>

namespace vine
{
    Rect::Rect()
        : repr_({ 0.0f, 0.0f, 0.0f, 0.0f }), x(repr_.x), y(repr_.y), w(repr_.z), h(repr_.w)
    {
    }

    Rect::Rect(float x, float y, float w, float h)
        : repr_({ x,y, w, h }), x(repr_.x), y(repr_.y), w(repr_.z), h(repr_.w)
    {
    }

    Rect::~Rect()
    {
    }

    Rect::Rect(const Rect& other)
        : repr_(other.repr_), x(repr_.x), y(repr_.y), w(repr_.z), h(repr_.w)
    {
    }

    Rect& Rect::operator=(const Rect& other)
    {
        if (&other != this)
            repr_ = other.repr_;

        return *this;
    }

    bool Rect::contains(const Vec2& point) const
    {
        return (point.x >= x &&
                point.x <= x + w &&
                point.y >= y &&
                point.y <= y + h);
    }

    void Rect::centerAt(const Vec2& point)
    {
        x = point.x - (w / 2.0f);
        y = point.y - (h / 2.0f);
    }
}