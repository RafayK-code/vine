#include <vine/core/Application.h>

#include <vine/events/WindowEvent.h>
#include <vine/core/Logger.h>
#include <vine/renderer/Renderer.h>

#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/SpriteSheet.h>
#include <vine/renderer/renderable/Quad.h>

#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceImage.h>
#include <vine/resource/ResourceSprite.h>

#include <vine/renderer/backend/Font.h>

#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <filesystem>

namespace vine
{
    SpriteRef sprite;
    Renderable* quad;

    SpriteSheet* sheet;
    ResourceHandle handle;

    FontRef font;

    Application::Application()
    {
        Logger::init();
        DBG_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL could not be initialized");

        ResourceManager::init();

        window_ = new Window({ "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 });
        DBG_INFO("Window created successfully");

        Renderer::init(window_->getNativePtr());
        glViewport(0, 0, window_->getWidth(), window_->getHeight());
        Renderer::ref().setClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

        window_->addEventCallback<WindowCloseEvent>([this](WindowCloseEvent& e) {
            running_ = false;
        });

        running_ = true;

        SpriteState state;
        state.pos = { 500.0f, 100.0f };
        state.scale = { 50.0f, 50.0f };
        state.layer = 1.0f;
        state.rotation = 0.0f;
        handle = ResourceManager::ref().createAndLoadResource<ResourceSprite, ResourceSpriteCreationData>(ResourceSpriteCreationData("assets/spritesheets/demo/sheet.png", state));
        sprite = ResourceManager::ref().getResource<ResourceSprite>(handle)->getSprite();

        sheet = new SpriteSheet("assets/spritesheets/demo/sheet.xml");
        Sprite* s = sheet->getSprite("wall_texture_gold.png");
        s->setPosition({ 200.0f, 200.0f });
        s->setScale({ 100.0f, 100.0f });

        quad = new Quad(RenderableState());
        quad->setPosition({ 600.0f, 500.0f });
        quad->setScale({ 100.0f, 100.0f });
        quad->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });

        font = Font::getDefault();
    }

    Application::~Application()
    {
        delete quad;
        font = nullptr;
        sprite = nullptr;
        delete sheet;
        Renderer::shutdown();
        delete window_;
        SDL_Quit();

        ResourceManager::shutdown();
        DBG_INFO("Application successfully shutdown");
        Logger::shutdown();
    }

    void Application::run()
    {
        onTick();

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

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 600.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 1.0f));

        Renderer::TextParams params;
        params.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        Renderer::ref().drawText("Hello world!", font, transform, params);

        sheet->getSprite("wall_texture_gold.png")->render();
        quad->render();
        Renderer::ref().endScene();



        window_->tick();
    }
}