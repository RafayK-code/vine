#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>
#include <vine/renderer/Renderer.h>

#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/Quad.h>
#include <vine/renderer/renderable/Text.h>
#include <vine/renderer/renderable/RenderableManager.h>

#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/resource/ResourceFont.h>

#include <vine/renderer/backend/Font.h>

#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>

namespace vine
{
    Application::Application(const ApplicationCreationSettings& settings)
    {
        Logger::init();
        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        ResourceManager::init();

        window_ = new Window(settings.windowProps);
        DBG_INFO("Window created successfully");

        Renderer::init(window_->getNativePtr());
        glViewport(0, 0, window_->getWidth(), window_->getHeight());
        Renderer::ref().setClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });

        RenderableManager::init();

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        running_ = true;
    }

    Application::~Application()
    {
        RenderableManager::shutdown();
        Renderer::shutdown();
        if (window_)
            delete window_;
        ResourceManager::shutdown();
        SDL_Quit();
        DBG_INFO("Application successfully shutdown");
        Logger::shutdown();
    }

    void Application::tick()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_WINDOWEVENT)
            {
                window_->dispatchSDLEvents(&e);
            }
        }

        onTick();

        window_->tick();
    }
}