#pragma once

#include <vine/resource/Resource.h>
#include <vine/renderer/renderable/SpriteSheet.h>

namespace vine
{
    class ResourceSpriteSheetCreationData : public ResourceCreationData
    {
    public:
        ResourceSpriteSheetCreationData(const std::string& file, const RenderableState& state = RenderableState());
        ResourceSpriteSheetCreationData(const ResourceSpriteSheetCreationData& other);

        virtual ~ResourceSpriteSheetCreationData();

        virtual ResourceCreationData* clone() const override;

        RenderableState state;
    };

    class ResourceSpriteSheet : public Resource
    {
    public:
        virtual ~ResourceSpriteSheet();

        virtual void load();
        virtual void unload();

        SpriteSheetRef getSpriteSheet() const { return sheet_; }

    protected:
        ResourceSpriteSheet(const ResourceSpriteSheetCreationData& data);

    private:
        SpriteSheetRef sheet_;
    };
}