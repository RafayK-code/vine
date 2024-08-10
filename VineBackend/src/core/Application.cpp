#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>
#include <vine/renderer/Renderer.h>

#include <vine/renderer/renderable/Sprite.h>

#include <iostream>

#include <glad/glad.h>

#include <filesystem>

namespace vine
{
    TextureRef tex;
    IRenderable* sprite;

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

        RenderableState state;
        state.pos = { 100.0f, 100.0f };
        state.scale = { 200.0f, 200.0f };
        state.layer = 1.0f;
        state.rotation = 45.0f;
        sprite = new Sprite("assets/images/goblin_king.png", state);
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

        Renderer::ref().setClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
        Renderer::ref().clear();
        OrthographicCamera cam(0, 1280, 0, 720, -0.1f, -100.0f);
        Renderer::ref().beginScene(cam);
        // z is how many units away from the screen --> maybe renderer can handle the flip?
        Renderer::ref().drawQuad({ 100.0f, 100.0f, 50.5f }, { 500.0f, 200.0f }, { 0.4f, 1.0f, 1.0f, 1.0f });
        //Renderer::drawQuad({ 50.0f, 50.0f, 10.0f }, { 200.0f, 200.0f }, tex);
        //Renderer::drawQuad({ 100.0f, 100.0f, 50.5f }, { 200.0f, 200.0f }, tex);
        sprite->render();
        Renderer::ref().endScene();

        window_->tick();
    }
}