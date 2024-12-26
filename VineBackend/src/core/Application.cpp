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

#include <vine/events/AppEvent.h>

#include <vine/controller/KeyboardMouseController.h>

#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>
#include <chrono>

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

        switch (settings.controllerType)
        {
        case Controller::Type::Keyboard:
            controller_ = new KeyboardMouseController();
            break;
        default:
            controller_ = nullptr;
        }

        running_ = true;
    }

    Application::~Application()
    {
        if (controller_)
            delete controller_;
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
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();

        float dt = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        onTick();
        window_->tick();

        processSDLEvents();

        AppTickEvent e(dt);
        dispatchEvent(e);
    }

    void Application::processSDLEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_WINDOWEVENT:
                window_->dispatchSDLEvents(&e);
                break;
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_TEXTINPUT:
                if (controller_->getType() == Controller::Type::Keyboard)
                    controller_->dispatchSDLEvents(&e);
                break;
            }
        }
    }
}