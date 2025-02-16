#pragma once

#include <vine/renderer/renderable/Renderable.h>
#include <vine/renderer/OrthographicCamera.h>

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

        const Ref<OrthographicCamera>& getCamera() const { return camera_; }
        Ref<OrthographicCamera> getCamera() { return camera_; }
        void setCamera(const Ref<OrthographicCamera>& camera) { camera_ = camera; }

        using RenderableList = std::vector<Renderable*>;
        const RenderableList& getRenderables() const { return renderables_; }

    private:
        Ref<OrthographicCamera> camera_;
        RenderableLayerLevel layer_;

        RenderableList renderables_;
    };
}