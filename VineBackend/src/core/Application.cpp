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
        DBG_INFO("Logging initialized");

        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        ResourceManager::init();
        DBG_INFO("Resource manager initialized");

        window_ = new Window(settings.windowProps);
        DBG_INFO("Window created successfully");

        Renderer::init(window_);
        DBG_INFO("Renderer initialized");

        Renderer::ref().setViewport({ 0, 0, window_->getWidth(), window_->getHeight() });
        Renderer::ref().setClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });

        RenderableManager::init();

        windowListener_.listen<WindowCloseEvent>(*window_, [this](const WindowCloseEvent& e) {
            running_ = false;
        });

        windowListener_.listen<WindowResizeEvent>(*window_, [](const WindowResizeEvent& e) {
            Renderer::ref().setViewport({ 0, 0, e.getWidth(), e.getHeight() });
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
        DBG_INFO("Application startup successful");
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

        window_->tick();

        processSDLEvents();

        onTick(dt);
        AppTickEvent e(dt);
        dispatchEvent(e);
    }

    void Application::processSDLEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            window_->dispatchSDLEvents(&e);
            controller_->dispatchSDLEvents(&e);
        }
    }
}