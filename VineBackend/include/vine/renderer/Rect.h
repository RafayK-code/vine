#pragma once

#include <glm/glm.hpp>

namespace vine
{
    using Vec4 = glm::vec4;
    using Vec2 = glm::vec2;

    class Rect
    {
    public:
        Rect();
        Rect(float x, float y, float w, float h);

        ~Rect();

        Rect(const Rect& other);
        Rect& operator=(const Rect& other);

        float& x;
        float& y;
        float& w;
        float& h;

        bool contains(const Vec2& point) const;
        void centerAt(const Vec2& point);

        const Vec4& asVec4() const { return repr_; }

    private:
        Vec4 repr_;
    };
}