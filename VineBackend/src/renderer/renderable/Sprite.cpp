#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/core/Logger.h>

namespace vine
{
    Sprite::Sprite(const std::string& file , const RenderableState& state, const Rect& atlasRect)
        : Renderable(state), atlasRect_(atlasRect)
    {
        texture_ = ResourceImage::create(file);
        setShader("QuadShader");
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, { atlasRect_.x, atlasRect_.y }, { atlasRect_.w, atlasRect_.h }, getColor());
    }

    Ref<Renderable> Sprite::clone() const
    {
        return Ref<Sprite>(new Sprite(*this));
    }
}