#pragma once

namespace vine
{
    class Application
    {
    public:
        Application();
        ~Application();

        void run();
    };

    Application* createApplication(int argc, char** argv);
}