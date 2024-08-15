#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Sprite::Sprite(const std::string& image, const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale)
    {
        texture_ = createTexture(image);
    }

    Sprite::Sprite(const TextureRef& texture, const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale), texture_(texture)
    {
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getSpritePos(), getSpriteScale(), getColor());
    }

    SpriteRef createSprite(const std::string& image, const SpriteState& state)
    {
        return std::make_shared<Sprite>(image, state);
    }

    SpriteRef createSprite(const TextureRef& texture, const SpriteState& state)
    {
        return std::make_shared<Sprite>(texture, state);
    }
}