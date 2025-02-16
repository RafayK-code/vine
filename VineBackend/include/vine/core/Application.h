#pragma once

#include <vine/window/Window.h>
#include <vine/renderer/GraphicsContext.h>
#include <vine/events/Event.h>
#include <vine/controller/Controller.h>
#include <vine/events/EventListener.h>

namespace vine
{
    struct ApplicationCreationSettings
    {
        WindowProps windowProps;
        Controller::Type controllerType = Controller::Type::Keyboard;
    };

    class Application : public EventDispatcher
    {
    public:
        Application(const ApplicationCreationSettings& settings);
        virtual ~Application();

        virtual void onInit() {}
        virtual void onTick(float dt) {}
        virtual void onShutdown() {}

        void tick();

        bool isRunning() const { return running_; }

        Window* getWindow() { return window_; }
        Controller* getController() { return controller_; }

        static Application& ref() { return *instance_; }
        static Application* ptr() { return instance_; }

    private:
        void processSDLEvents();

    private:
        bool running_;

        Window* window_;
        Controller* controller_;

        EventListener windowListener_;
        static Application* instance_;
    };

    Application* createApplication(int argc, char** argv);
}