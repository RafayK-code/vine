#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>
#include <vine/renderer/Renderer.h>

#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/Quad.h>

#include <iostream>

#include <glad/glad.h>

#include <filesystem>

namespace vine
{
    IRenderable* sprite;
    IRenderable* quad;

    Application::Application()
    {
        Logger::init();
        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        window_ = new Window({ "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 });
        DBG_INFO("Window created successfully");

        Renderer::init(window_->getNativePtr());
        glViewport(0, 0, window_->getWidth(), window_->getHeight());
        Renderer::ref().setClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        running_ = true;

        RenderableState state;
        state.pos = { 100.0f, 100.0f };
        state.scale = { 200.0f, 200.0f };
        state.layer = 1.0f;
        state.rotation = 45.0f;
        sprite = new Sprite("assets/images/goblin_king.png", state);

        quad = new Quad(RenderableState());
        quad->setPosition({ 600.0f, 500.0f });
        quad->setScale({ 100.0f, 100.0f });
        quad->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    }

    Application::~Application()
    {
        delete quad;
        delete sprite;
        Renderer::shutdown();
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

        Renderer::ref().clear();
        OrthographicCamera cam(0, 1280, 0, 720, -0.1f, -100.0f);
        Renderer::ref().beginScene(cam);
        // z is how many units away from the screen --> maybe renderer can handle the flip?
        sprite->render();
        quad->render();
        Renderer::ref().endScene();

        window_->tick();
    }
}