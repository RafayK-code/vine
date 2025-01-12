#pragma once

#include <cmath>

namespace vine
{
    class Math
    {
    public:
        static constexpr float PI = 3.14159265358979323846f;
        static constexpr float TWO_PI = 2 * PI;
        static constexpr float HALF_PI = PI / 2;

        static inline float sin(float angle) { return std::sinf(angle); }
        static inline float cos(float angle) { return std::cosf(angle); }
        static inline float tan(float angle) { return std::tanf(angle); }

        static inline float atan2(float y, float x) { return std::atan2f(y, x); }

        static inline float degToRad(float deg) { return deg * (PI / 180.0f); }
        static inline float radToDeg(float rad) { return rad * (180.0f / PI); }

        static inline float pow(float base, float exp) { return std::pow(base, exp); }
        static inline float sqrt(float num) { return std::sqrtf(num); }

        static inline float round(float num) { return (num > 0) ? std::floorf(num + 0.5f) : std::ceilf(num - 0.5f); }

        static inline float lerp(float lerp, float a, float b) { return a + lerp * (b - a); }
        static inline float clamp(float val, float min, float max)
        {
            if (val < min)
                return min;
            if (val > max)
                return max;

            return val;
        }
    };
}