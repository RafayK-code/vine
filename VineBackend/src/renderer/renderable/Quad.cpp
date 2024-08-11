#include <vine/renderer/renderable/Quad.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Quad::Quad(const RenderableState& state)
        : Renderable(state)
    {
    }

    Quad::~Quad()
    {
    }

    void Quad::render() const
    {
        Renderer::ref().drawQuad(getTransform(), getColor());
    }
}