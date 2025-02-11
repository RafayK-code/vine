#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/backend/Texture.h>
#include <vine/resource/ResourceImage.h>

#include <vine/renderer/Rect.h>

namespace vine
{
    class Sprite : public Renderable
    {
    public:
        Sprite(const std::string& file, const RenderableState& state, const Rect& atlasRect = {-1.0f, -1.0f, -1.0f, -1.0f});

        virtual ~Sprite();

        virtual void render() const override;
        virtual Ref<Renderable> clone() const override;

        const Rect& getAtlasRect() const { return atlasRect_; }
        void setAtlasRect(const Rect& atlasRect) { atlasRect_ = atlasRect; }

    private:
        Rect atlasRect_;

        Ref<ResourceImage> texture_;
    };
}