#pragma once

#include <vine/window/Window.h>
#include <vine/renderer/GraphicsContext.h>
#include <vine/events/Event.h>
#include <vine/controller/Controller.h>

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
        virtual void onTick() {}
        virtual void onShutdown() {}

        void tick();

        bool isRunning() const { return running_; }

        Window* getWindow() const { return window_; }
        Controller* getController() const{ return controller_; }

    private:
        void processSDLEvents();

    private:
        bool running_;

        Window* window_;
        Controller* controller_;
    };

    Application* createApplication(int argc, char** argv);
}