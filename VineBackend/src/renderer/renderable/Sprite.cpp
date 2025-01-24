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
        /*
        res_ = ResourceManager::ref().getResource<ResourceImage>(textureHandle);
        DBG_ASSERT(res_, "Texture resource with given handle could not be found");

        if (!res_->isLoaded())
            res_->load();

        texture_ = res_->getTexture();
        setShader("QuadShader");
        */

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

    Renderable* Sprite::clone() const
    {
        return new Sprite(*this);
    }
}