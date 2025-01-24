#pragma once

#include <vine/resource/Resource.h>
#include <vine/resource/ResourceImage.h>

namespace vine
{
    struct MSDFData;

    class ResourceFont : public Resource
    {
        friend class ResourceManager;
    public:
        static Ref<ResourceFont> create(const std::string& file);

        virtual ~ResourceFont();

        virtual void reload() override;
        virtual void unload() override;

        const MSDFData* getData() const { return data_; }
        const Ref<ResourceImage>& getAtlasTexture() const { return atlasTexture_; }

    protected:
        ResourceFont(const ResourceCreationData& data);

    private:
        void loadFromFont();

    private:
        MSDFData* data_;
        Ref<ResourceImage> atlasTexture_;
    };
}