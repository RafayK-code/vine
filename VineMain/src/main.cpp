#include <SDL.h>

#include <vine/core/Application.h>
#include <vine/core/EntryPoint.h>

class MyApp : public vine::Application
{
public:
    MyApp() {}
    ~MyApp() {}
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    return new MyApp;
}