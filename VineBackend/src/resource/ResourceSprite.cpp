#include <vine/resource/ResourceSprite.h>

namespace vine
{
    ResourceSpriteCreationData::ResourceSpriteCreationData(const std::string& file, const SpriteState& state)
        : ResourceCreationData(file), state(state)
    {
    }

    ResourceSpriteCreationData::ResourceSpriteCreationData(const ResourceSpriteCreationData& other)
        : ResourceCreationData(other), state(other.state)
    {
    }

    ResourceSpriteCreationData::~ResourceSpriteCreationData()
    {
    }

    ResourceCreationData* ResourceSpriteCreationData::clone() const
    {
        return new ResourceSpriteCreationData(*this);
    }

    ResourceSprite::ResourceSprite(const ResourceSpriteCreationData& data)
        : Resource(data)
    {
        creationData_->type = ResourceDataType::ResourceDataTypeImage;
    }

    ResourceSprite::~ResourceSprite()
    {
        unload();
    }

    void ResourceSprite::load()
    {
        if (loaded_)
            return;

        sprite_ = createSprite(creationData_->file, dynamic_cast<ResourceSpriteCreationData*>(creationData_)->state);
        loaded_ = true;
    }

    void ResourceSprite::unload()
    {
        if (!loaded_)
            return;

        sprite_ = nullptr;
        loaded_ = false;
    }
}