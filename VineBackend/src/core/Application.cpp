#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>
#include <vine/renderer/Renderer.h>

#include <iostream>

#include <glad/glad.h>

#include <filesystem>

namespace vine
{
    Application::Application()
    {
        Logger::init();
        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        window_ = new Window({ "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 });
        DBG_INFO("Window created successfully");

        context_.createContext(window_->getNativePtr());

        glViewport(0, 0, window_->getWidth(), window_->getHeight());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        Renderer::init();

        running_ = true;
    }

    Application::~Application()
    {
        context_.destroyContext();
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

        glClear(GL_COLOR_BUFFER_BIT);
        OrthographicCamera cam(-1, 1, -1, 1);
        Renderer::beginScene(cam);
        Renderer::drawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
        Renderer::endScene();

        window_->tick();
    }
}