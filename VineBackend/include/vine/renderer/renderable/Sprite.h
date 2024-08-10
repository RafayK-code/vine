#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Texture.h>

namespace vine
{
    class Sprite : public IRenderable
    {
    public:
        Sprite(const std::string& texturePath, const RenderableState& state);
        Sprite(const TextureRef& texture, const RenderableState& state);

        virtual ~Sprite();

        virtual void render() override;

        const TextureRef& getTexture() const { return texture_; }
        void setTexture(const TextureRef& texture) { texture_ = texture; }

    private:
        TextureRef texture_;
    };
}