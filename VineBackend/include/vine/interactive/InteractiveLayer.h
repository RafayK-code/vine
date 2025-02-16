#pragma once

#include <vine/interactive/Interactive.h>
#include <vine/renderer/OrthographicCamera.h>

#include <vine/events/MouseEvent.h>
#include <vine/events/KeyEvent.h>

#include <map>

namespace vine
{
    class InteractiveLayer
    {
    public:
        InteractiveLayer(LayerLevel layer);
        ~InteractiveLayer();

        void add(Interactive* interactive);
        void remove(Interactive* interactive);

        bool onMouseButtonDown(const MouseButtonDownEvent& e);
        bool onMouseButtonUp(const MouseButtonUpEvent& e);

        const Ref<OrthographicCamera>& getCamera() const { return camera_; }
        Ref<OrthographicCamera> getCamera() { return camera_; }
        void setCamera(const Ref<OrthographicCamera>& camera) { camera_ = camera; }

        LayerLevel getLayer() const { return layer_; }

    private:
        using InteractiveList = std::vector<Interactive*>;
        InteractiveList interactives_;

        LayerLevel layer_;
        Ref<OrthographicCamera> camera_;
    };
}