#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/renderable/RenderableLayer.h>
#include <vine/resource/Resource.h>
#include <vine/util/Singleton.h>

#include <vector>
#include <map>

namespace vine
{
    class RenderableManager : public Singleton<RenderableManager>
    {
        friend class Singleton<RenderableManager>;
    public:
        ~RenderableManager();

        static void init();
        static void shutdown();

        void render() const;

        RenderableLayer* getLayer(RenderableLayerLevel layer);

        ResourceHandle createSpritesFromSheet(const std::string& sheet, const RenderableState& defaultState = RenderableState());

    private:
        RenderableManager();

    private:
        class DescendingComparator 
        {
        public:
            bool operator()(const RenderableLayerLevel& lhs, const RenderableLayerLevel& rhs) const
            {
                return lhs > rhs; // Reverse the default order
            }
        };

        std::map<RenderableLayerLevel, RenderableLayer*, DescendingComparator> renderables_;
    };
}