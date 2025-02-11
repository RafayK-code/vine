#pragma once

#include <vine/renderer/renderable/builder/RenderableBuilder.h>

#include <vine/renderer/renderable/Sprite.h>

namespace vine
{
    class SpriteRenderableBuilder : public RenderableBuilderT<SpriteRenderableBuilder, Sprite>
    {
    public:
        SpriteRenderableBuilder(const std::string& imgFile);
        virtual ~SpriteRenderableBuilder();

        virtual Ref<Renderable> create() const override;

        SpriteRenderableBuilder& setAtlasRect(const Rect& atlas);

    private:
        std::string imgFile_;

        Rect atlasRect_;
    };
}