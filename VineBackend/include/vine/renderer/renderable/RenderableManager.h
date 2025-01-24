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

        Renderable* addRenderable(const std::string& name, Renderable* renderable);
        
        template<typename T, typename... Args>
        Renderable* createRenderable(const std::string& name, Args&&... args)
        {
            Renderable* renderable = new T(std::forward<Args>(args)...);
            return addRenderable(name, renderable);
        }

        Renderable* getRenderable(const std::string& name);
        void removeRenderable(const std::string& name);

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