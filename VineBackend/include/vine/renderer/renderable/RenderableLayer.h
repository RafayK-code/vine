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

        void add(Renderable* renderable);
        void remove(Renderable* renderable);

        RenderableLayerLevel getLayer() const { return layer_; }

        using RenderableList = std::vector<Renderable*>;
        const RenderableList& getRenderables() const { return renderables_; }

    private:
        RenderableLayerLevel layer_;

        RenderableList renderables_;
    };
}