#include <vine/renderer/renderable/builder/SpriteRenderableBuilder.h>

namespace vine
{
    SpriteRenderableBuilder::SpriteRenderableBuilder(const std::string& imgFile)
        : imgFile_(imgFile), atlasRect_(-1.0f, -1.0f, -1.0f, -1.0f)
    {
    }

    SpriteRenderableBuilder::~SpriteRenderableBuilder()
    {
    }

    Ref<Renderable> SpriteRenderableBuilder::create() const
    {
        return Ref<Sprite>(new Sprite(imgFile_, state_, atlasRect_));
    }

    SpriteRenderableBuilder& SpriteRenderableBuilder::setAtlasRect(const Rect& atlasRect)
    {
        atlasRect_ = atlasRect;
        return *this;
    }
}