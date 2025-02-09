#include <vine/renderer/Color.h>

namespace vine
{
    Color::Color(float r, float g, float b, float a, bool normalized)
        : glm::vec4(r, g, b, a), normalized_(normalized)
    {
    }

    Color::~Color()
    {
    }

    void Color::normalize()
    {
        if (normalized_)
            return;

        r /= 255.0f;
        g /= 255.0f;
        b /= 255.0f;
        a /= 255.0f;

        normalized_ = true;
    }

    void Color::denormalize()
    {
        if (!normalized_)
            return;

        r *= 255.0f;
        g *= 255.0f;
        b *= 255.0f;
        a *= 255.0f;

        normalized_ = false;
    }
}