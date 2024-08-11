#pragma once

#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/backend/Texture.h>

namespace vine
{
    class SpriteImmediate : public Sprite
    {
    public:
        SpriteImmediate(const std::string& texturePath, const SpriteState& state);
        SpriteImmediate(const TextureRef& texture, const SpriteState& state);

        virtual ~SpriteImmediate();

        virtual void render() const override;

        const TextureRef& getTexture() const { return texture_; }
        void setTexture(const TextureRef& texture) { texture_ = texture; }

    private:
        TextureRef texture_;
    };
}