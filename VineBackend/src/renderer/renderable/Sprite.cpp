#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/core/Logger.h>

namespace vine
{
    Sprite::Sprite(const std::string& file , const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale)
    {
        texture_ = ResourceImage::create(file);
        setShader("QuadShader");
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getSpritePos(), getSpriteScale(), getColor());
    }

    Ref<Renderable> Sprite::clone() const
    {
        SpriteState state;
        state.pos = getState().pos;
        state.scale = getState().scale;
        state.rotation = getState().rotation;
        state.color = getState().color;
        state.layer = getState().layer;
        state.priority = getState().priority;
        state.visible = getState().visible;
        state.spritePos = spritePos_;
        state.spriteScale = spriteScale_;

        Sprite* sprite = new Sprite(texture_->getFile(), state);
        return Ref<Sprite>(sprite);
    }
}