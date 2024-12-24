#include <vine/renderer/renderable/Sprite.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/Renderer.h>
#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/core/Logger.h>

namespace vine
{
    Sprite::Sprite(const Handle& textureHandle, const SpriteState& state)
        : Renderable(state), spritePos_(state.spritePos), spriteScale_(state.spriteScale), textureHandle_(textureHandle)
    {
        ResourceImage* resTex = ResourceManager::ref().getResource<ResourceImage>(textureHandle_);
        DBG_ASSERT(resTex, "Texture resource with given handle could not be found");

        if (!resTex->isLoaded())
            resTex->load();

        texture_ = resTex->getTexture();
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