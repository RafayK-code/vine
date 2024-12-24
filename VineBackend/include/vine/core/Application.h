#pragma once

#include <vine/window/Window.h>
#include <vine/renderer/GraphicsContext.h>

namespace vine
{
    struct ApplicationCreationSettings
    {
        WindowProps windowProps;
    };

    class Application
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

    private:
        bool running_;

        Window* window_;
    };

    Application* createApplication(int argc, char** argv);
}