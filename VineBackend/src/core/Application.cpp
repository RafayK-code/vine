#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>

#include <iostream>

#include <glad/glad.h>

SDL_GLContext mainContext;

namespace vine
{
    Application::Application()
    {
        Logger::init();
        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        window_ = new Window({ "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 });
        DBG_INFO("Window created successfully");

        mainContext = SDL_GL_CreateContext(window_->getNativePtr());

        gladLoadGLLoader(SDL_GL_GetProcAddress);
        glViewport(0, 0, window_->getWidth(), window_->getHeight());
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        running_ = true;
    }

    Application::~Application()
    {
        delete window_;
        SDL_Quit();

        DBG_INFO("Application successfully shutdown");
        Logger::shutdown();
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

        window_->tick();
    }
}