#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Texture.h>

namespace vine
{
    struct SpriteState : public RenderableState
    {
        glm::vec2 spritePos = { -1.0f, -1.0f };
        glm::vec2 spriteScale = { -1.0f, -1.0f };
    };

    class Sprite : public Renderable
    {
    public:
        Sprite(const std::string& image, const SpriteState& state);
        Sprite(const TextureRef& texture, const SpriteState& state);

        virtual ~Sprite();

        virtual void render() const override;

        const glm::vec2& getSpritePos() const { return spritePos_; }
        void setSpritePos(const glm::vec2& spritePos) { spritePos_ = spritePos; }

        const glm::vec2& getSpriteScale() const { return spriteScale_; }
        void setSpriteScale(const glm::vec2& spriteScale) { spriteScale_ = spriteScale; }

        const TextureRef& getTexture() const { return texture_; }

    private:
        glm::vec2 spritePos_;
        glm::vec2 spriteScale_;

        TextureRef texture_;
    };

    using SpriteRef = std::shared_ptr<Sprite>;

    SpriteRef createSprite(const std::string& image, const SpriteState& state);
    SpriteRef createSprite(const TextureRef& texture, const SpriteState& state);
}