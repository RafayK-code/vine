#include <vine/resource/ResourceScript.h>

namespace vine
{
    ResourceScript::ResourceScript(const ResourceCreationData& data)
        : Resource(data), script_(nullptr)
    {
        creationData_->type = ResourceDataType::ResourceDataTypeScript;
    }

    ResourceScript::~ResourceScript()
    {
        unload();
    }

    void ResourceScript::load()
    {
        if (loaded_)
            return;

        script_ = createScript(creationData_->file);
        loaded_ = true;
    }

    void ResourceScript::unload()
    {
        if (!loaded_)
            return;

        script_ = nullptr;
        loaded_ = false;
    }
}