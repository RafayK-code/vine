#include <vine/renderer/renderable/builder/QuadRenderableBuilder.h>

namespace vine
{
    QuadRenderableBuilder::QuadRenderableBuilder()
    {
    }

    QuadRenderableBuilder::~QuadRenderableBuilder()
    {
    }

    Ref<Renderable> QuadRenderableBuilder::create() const
    {
        return Ref<Quad>(new Quad(state_));
    }
}