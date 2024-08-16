#include <vine/resource/ResourceSpriteSheet.h>

namespace vine
{
    ResourceSpriteSheetCreationData::ResourceSpriteSheetCreationData(const std::string& file, const RenderableState& state)
        : ResourceCreationData(file), state(state)
    {
    }

    ResourceSpriteSheetCreationData::ResourceSpriteSheetCreationData(const ResourceSpriteSheetCreationData& other)
        : ResourceCreationData(other), state(other.state)
    {
    }

    ResourceSpriteSheetCreationData::~ResourceSpriteSheetCreationData()
    {
    }

    ResourceCreationData* ResourceSpriteSheetCreationData::clone() const
    {
        return new ResourceSpriteSheetCreationData(*this);
    }

    ResourceSpriteSheet::ResourceSpriteSheet(const ResourceSpriteSheetCreationData& data)
        : Resource(data)
    {
        creationData_->type = ResourceDataType::ResourceDataTypeImage;
    }

    ResourceSpriteSheet::~ResourceSpriteSheet()
    {
        unload();
    }

    void ResourceSpriteSheet::load()
    {
        if (loaded_)
            return;

        sheet_ = createSpriteSheet(creationData_->file, dynamic_cast<ResourceSpriteSheetCreationData*>(creationData_)->state);
        loaded_ = true;
    }

    void ResourceSpriteSheet::unload()
    {
        if (!loaded_)
            return;

        sheet_ = nullptr;
        loaded_ = false;
    }
}