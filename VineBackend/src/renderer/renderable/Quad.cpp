#include <vine/renderer/renderable/Quad.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Quad::Quad(const RenderableState& state)
    {
        setState(state);
    }

    Quad::~Quad()
    {
    }

    void Quad::render()
    {
        Renderer::ref().drawQuad(getTransform(), getColor());
    }
}