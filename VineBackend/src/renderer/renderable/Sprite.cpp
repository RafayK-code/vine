#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/Renderer.h>

namespace vine
{
    Sprite::Sprite(const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale)
    {
    }

    Sprite::~Sprite()
    {
    }
}