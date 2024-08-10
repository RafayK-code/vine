#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Sprite::Sprite(const std::string& texturePath, const RenderableState& state)
    {
        setState(state);
        texture_ = createTexture(texturePath);
    }

    Sprite::Sprite(const TextureRef& texture, const RenderableState& state)
        : texture_(texture)
    {
        setState(state);
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render()
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getColor());
    }
}