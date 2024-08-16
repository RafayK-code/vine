#pragma once

#include <vine/resource/Resource.h>
#include <vine/renderer/renderable/Sprite.h>

namespace vine
{
    class ResourceSpriteCreationData : public ResourceCreationData
    {
    public:
        ResourceSpriteCreationData(const std::string& file, const SpriteState& state);
        ResourceSpriteCreationData(const ResourceSpriteCreationData& other);

        virtual ~ResourceSpriteCreationData();

        virtual ResourceCreationData* clone() const override;

        SpriteState state;
    };

    class ResourceSprite : public Resource
    {
        friend class ResourceManager;
    public:
        virtual ~ResourceSprite();

        virtual void load() override;
        virtual void unload() override;

        SpriteRef getSprite() const { return sprite_; }

    protected:
        ResourceSprite(const ResourceSpriteCreationData& data);

    private:
        SpriteRef sprite_;
    };
}