#pragma once

#include <vine/resource/Resource.h>
#include <vine/util/Singleton.h>
#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/SpriteSheet.h>

#include <unordered_map>

namespace vine
{
    class ResourceManager : public Singleton<ResourceManager>
    {
        friend class Singleton<ResourceManager>;
    public:
        ~ResourceManager();

        void init();
        void shutdown();

        ResourceHandle addSprite(const std::string& image, const SpriteState& state);
        ResourceHandle addSprite(const TextureRef& texture, const SpriteState& state);

        ResourceHandle addSpriteSheet(const std::string& sheet, const RenderableState& defaultState = RenderableState());

        const Sprite& getSprite(const ResourceHandle& handle) const;
        const SpriteSheet& getSpriteSheet(const ResourceHandle& handle) const;

        void deleteSprite(const ResourceHandle& handle);
        void deleteSpriteSheet(const ResourceHandle& handle);

    private:
        ResourceManager();

    private:
        std::unordered_map<ResourceHandle, ResourceBase> resources_;
    };
}