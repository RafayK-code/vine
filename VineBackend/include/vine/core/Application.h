#pragma once

#include <vine/window/Window.h>
#include <vine/renderer/GraphicsContext.h>

namespace vine
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void onInit() {}
        virtual void onTick() {}
        virtual void onShutdown() {}

        void run();

        bool isRunning() const { return running_; }

    private:
        bool running_;

        Window* window_;
    };

    Application* createApplication(int argc, char** argv);
}