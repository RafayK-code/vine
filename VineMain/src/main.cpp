#include <SDL.h>

#include <vine/core/Application.h>
#include <vine/core/EntryPoint.h>

#include <vine/renderer/Renderer.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/renderable/Sprite.h>
#include <vine/renderer/renderable/Quad.h>
#include <vine/renderer/renderable/Text.h>

#include <vine/resource/ResourceManager.h>
#include <vine/resource/ResourceFont.h>

class MyApp : public vine::Application
{
public:
    MyApp(const vine::ApplicationCreationSettings& settings) 
        : Application(settings)
    {
    }

    ~MyApp() {}

    void onInit() override 
    {
        using namespace vine;

        RenderableManager::ref().createSpritesFromSheet("assets/spritesheets/demo/sheet.xml");
        Renderable* s = RenderableManager::ref().getRenderable("wall_texture_gold.png");

        s->setPosition({ 200.0f, 200.0f });
        s->setScale({ 100.0f, 100.0f });

        Quad* quad = new Quad(RenderableState());
        quad->setPosition({ 600.0f, 500.0f });
        quad->setScale({ 100.0f, 100.0f });
        quad->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
        RenderableManager::ref().addRenderable("Quad", quad);

        Handle handle = ResourceManager::ref().createAndLoadResource<ResourceFont>({ "assets/fonts/opensans/OpenSans-Regular.ttf" });
        Text* text = new Text(handle, TextState());
        text->setPosition({ 0.0f, 600.0f });
        text->setLayer(1.0f);
        text->setScale({ 50.0f,50.0f });
        text->setText("hello\nworld!");
        text->setLineSpacing(-0.1f);

        RenderableManager::ref().addRenderable("Text", text);
    }

    void onTick() override 
    {
        using namespace vine;

        Renderer::ref().clear();
        OrthographicCamera cam(0, 1280, 0, 720, -0.1f, -100.0f);
        Renderer::ref().beginScene(cam);
        RenderableManager::ref().render();
        Renderer::ref().endScene();
    }

    void onShutdown() override 
    {
    }
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    ApplicationCreationSettings settings;
    settings.windowProps = { "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };
    return new MyApp(settings);
}