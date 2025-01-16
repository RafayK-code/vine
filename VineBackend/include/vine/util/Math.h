#pragma once

#include <cmath>

#include <glm/glm.hpp>

namespace vine
{
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Color = glm::vec4;

    class Math
    {
    public:
        static constexpr float PI = 3.14159265358979323846f;
        static constexpr float TWO_PI = 2 * PI;
        static constexpr float HALF_PI = PI / 2;

        static inline float sin(float angle) { return std::sin(angle); }
        static inline float cos(float angle) { return std::cos(angle); }
        static inline float tan(float angle) { return std::tan(angle); }

        static inline float atan2(float y, float x) { return std::atan2(y, x); }

        static inline float degToRad(float deg) { return deg * (PI / 180.0f); }
        static inline float radToDeg(float rad) { return rad * (180.0f / PI); }

        static inline float pow(float base, float exp) { return std::pow(base, exp); }
        static inline float sqrt(float num) { return std::sqrt(num); }

        static inline float round(float num) { return (num > 0) ? std::floor(num + 0.5f) : std::ceil(num - 0.5f); }

        static inline float lerp(float lerp, float a, float b) { return a + lerp * (b - a); }
        static inline float clamp(float val, float min, float max)
        {
            if (val < min)
                return min;
            if (val > max)
                return max;

            return val;
        }

        static inline Color normalizeColor(const Color& color) { return color / 255.0f; }
        static inline Color denormalizeColor(const Color& color) { return glm::round(color * 255.0f); }
    };
}