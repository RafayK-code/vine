#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/core/Logger.h>

namespace vine
{
    Sprite::Sprite(const ResourceHandle& textureHandle, const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale)
    {
        res_ = ResourceManager::ref().getResource<ResourceImage>(textureHandle);
        DBG_ASSERT(res_, "Texture resource with given handle could not be found");

        if (!res_->isLoaded())
            res_->load();

        texture_ = res_->getTexture();
        setShader("QuadShader");
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::render() const
    {
        Renderer::ref().drawQuad(getTransform(), texture_, getSpritePos(), getSpriteScale(), getColor());
    }
}