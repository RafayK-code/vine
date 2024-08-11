#include <vine/renderer/renderable/SpriteImmediate.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    SpriteImmediate::SpriteImmediate(const std::string& texturePath, const SpriteState& state)
        : Sprite(state)
    {
        texture_ = createTexture(texturePath);
    }

    SpriteImmediate::SpriteImmediate(const TextureRef& texture, const SpriteState& state)
        : Sprite(state), texture_(texture)
    {
    }

    SpriteImmediate::~SpriteImmediate()
    {
    }

    void SpriteImmediate::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getSpritePos(), getSpriteScale(), getColor());
    }
}