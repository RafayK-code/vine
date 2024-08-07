#pragma once

#include <vine/core/Application.h>

extern vine::Application* vine::createApplication(int argc, char** argv);

namespace vine
{
    int vineMain(int argc, char** argv)
    {
        Application* app = createApplication(argc, argv);
        while (app->isRunning())
        {
            app->run();
        }
        delete app;

        return 0;
    }
}

int main(int argc, char** argv)
{
    return vine::vineMain(argc, argv);
}