#pragma once

#include <vine/renderer/renderable/builder/RenderableBuilder.h>

#include <vine/renderer/renderable/Quad.h>

namespace vine
{
    class QuadRenderableBuilder : public RenderableBuilderT<QuadRenderableBuilder, Quad>
    {
    public:
        QuadRenderableBuilder();
        virtual ~QuadRenderableBuilder();

        virtual Ref<Renderable> create() const override;
    };
}