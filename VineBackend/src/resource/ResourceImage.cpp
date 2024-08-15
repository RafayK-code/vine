#include <vine/resource/ResourceImage.h>

namespace vine
{
    ResourceImage::ResourceImage(const ResourceCreationData& data)
        : Resource(data)
    {
        creationData_->type = ResourceDataType::ResourceDataTypeImage;
    }

    ResourceImage::~ResourceImage()
    {
        unload();
    }

    void ResourceImage::load()
    {
        if (loaded_)
            return;

        texture_ = createTexture(creationData_->file);
        loaded_ = true;
    }

    void ResourceImage::unload()
    {
        if (!loaded_)
            return;

        texture_ = nullptr;
        loaded_ = false;
    }
}