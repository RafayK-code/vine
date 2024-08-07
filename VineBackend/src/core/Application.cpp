#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>

#include <iostream>

namespace vine
{
    Application::Application()
    {
        SDL_Init(SDL_INIT_VIDEO);

        window_ = new Window({ "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 });

        window_->addEventCallback<WindowResizeEvent>([](WindowResizeEvent& e) {
            std::cout << "Hello: " << e.getWidth() << ", " << e.getHeight();
        });

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        running_ = true;
    }

    Application::~Application()
    {
        delete window_;
        SDL_Quit();
    }

    void Application::run()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_WINDOWEVENT)
            {
                window_->dispatchSDLEvents(&e);
            }
        }
    }
}