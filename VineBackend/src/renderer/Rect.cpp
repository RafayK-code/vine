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
}