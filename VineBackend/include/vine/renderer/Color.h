#pragma once

#include <glm/glm.hpp>

namespace vine
{
    class Color : public glm::vec4
    {
    public:
        using glm::vec4::vec4;

        Color(float r, float g, float b, float a, bool normalized = true);
        ~Color();

        void normalize();
        void denormalize();

        bool isNormalized() const { return normalized_; }

    private:
        bool normalized_ = true;
    };
}