#pragma once

#include <vine/renderer/renderable/Renderable.h>

namespace vine
{
    class Quad : public Renderable
    {
    public:
        Quad(const RenderableState& state);
        virtual ~Quad();

        virtual void render() const override;
    };
}