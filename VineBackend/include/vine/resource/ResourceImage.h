#pragma once

#include <vine/resource/Resource.h>
#include <vine/renderer/backend/Texture.h>

namespace vine
{
    class ResourceImage : public Resource
    {
        friend class ResourceManager;
    public:
        virtual ~ResourceImage();

        virtual void load() override;
        virtual void unload() override;

        TextureRef getTexture() const { return texture_; }

    protected:
        ResourceImage(const ResourceCreationData& data);

    private:
        TextureRef texture_;
    };
}