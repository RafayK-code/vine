#pragma once

#include <vine/renderer/renderable/Renderable.h>

#include <string>
#include <unordered_map>

namespace vine
{
    class RenderableLayer
    {
    public:
        RenderableLayer(RenderableLayerLevel layer);
        ~RenderableLayer();

        void render() const;

        Renderable* addRenderable(const std::string& name, Renderable* renderable);

        template<typename T, typename... Args>
        Renderable* createRenderable(const std::string& name, Args&&... args)
        {
            Renderable* renderable = new T(std::forward<Args>(args)...);
            return addRenderable(name, renderable);
        }

        Renderable* getRenderable(const std::string& name);
        bool hasRenderable(const std::string& name) const;
        void removeRenderable(const std::string& name);

        RenderableLayerLevel getLayer() const { return layer_; }

    private:
        RenderableLayerLevel layer_;

        std::unordered_map<std::string, Renderable*> renderables_;
    };
}