#include <SDL.h>

#include <vine/core/Application.h>
#include <vine/core/EntryPoint.h>

class MyApp : public vine::Application
{
public:
    MyApp() {}
    ~MyApp() {}

    void onInit() override {}
    void onTick() override {}
    void onShutdown() override {}
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    return new MyApp;
}