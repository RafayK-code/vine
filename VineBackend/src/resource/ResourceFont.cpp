#include <vine/resource/ResourceFont.h>

namespace vine
{
    ResourceFont::ResourceFont(const ResourceCreationData& data)
        : Resource(data)
    {
        creationData_->type = ResourceDataType::ResourceDataTypeFont;
    }

    ResourceFont::~ResourceFont()
    {
        unload();
    }

    void ResourceFont::load()
    {
        if (loaded_)
            return;

        font_ = createFont(creationData_->file);
        loaded_ = true;
    }

    void ResourceFont::unload()
    {
        if (!loaded_)
            return;

        font_ = nullptr;
        loaded_ = false;
    }
}