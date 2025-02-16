#pragma once

#include <vine/util/Singleton.h>
#include <vine/interactive/Interactive.h>
#include <vine/interactive/InteractiveLayer.h>
#include <vine/controller/Controller.h>
#include <vine/events/EventListener.h>

#include <vine/events/MouseEvent.h>
#include <vine/events/KeyEvent.h>

#include <vector>

namespace vine
{
    class InteractiveManager : public Singleton<InteractiveManager>
    {
        friend class Singleton<InteractiveManager>;
    public:
        ~InteractiveManager();

        static void init();
        static void shutdown();

        InteractiveLayer* getLayer(LayerLevel layer);

        Controller* getController() const { return controller_; }
        void setController(Controller* controller);

    private:
        InteractiveManager();

        void setupEventCallbacks();

        void onMouseButtonDown(const MouseButtonDownEvent& e);
        void onMouseButtonUp(const MouseButtonUpEvent& e);

    private:
        Controller* controller_;
        EventListener listener_;

        std::map<LayerLevel, InteractiveLayer*> interactives_;
    };
}