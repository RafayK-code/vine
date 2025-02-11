#pragma once

#include <glm/glm.hpp>

namespace vine
{
    using Vec4 = glm::vec4;

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

        const Vec4& asVec4() const { return repr_; }

    private:
        Vec4 repr_;
    };
}