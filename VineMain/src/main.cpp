#include <SDL.h>

#include <Vine.h>
#include <vine/renderer/backend/Framebuffer.h>

#include <glm/gtc/matrix_transform.hpp>

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

        FramebufferSpecification spec;
        spec.width = 1280;
        spec.height = 720;
        spec.attachments = {
            FramebufferAttachmentSpecification({
                {FramebufferTextureFormat::RGBA8},
                {FramebufferTextureFormat::DEPTH24STENCIL8}
            })
        };

        framebuffer_ = createFramebuffer(spec);

        RenderableManager::ref().createSpritesFromSheet("assets/spritesheets/demo/sheet.xml");
        Renderable* s = RenderableManager::ref().getRenderable("wall_texture_gold.png");

        s->setPosition({ 200.0f, 200.0f });
        s->setScale({ 100.0f, 100.0f });

        Quad* quad = new Quad(RenderableState());
        quad->setPosition({ 600.0f, 500.0f });
        quad->setScale({ 100.0f, 100.0f });
        quad->setColor({ 1.0f, 0.0f, 0.0f, 0.7f });
        RenderableManager::ref().addRenderable("Quad", quad);

        Handle handle = ResourceManager::ref().createAndLoadResource<ResourceFont>({ "assets/fonts/opensans/OpenSans-Regular.ttf" });
        Text* text = new Text(handle, TextState());
        text->setPosition({ 600.0f, 500.0f });
        text->setLayer(Layer::Background);
        text->setScale({ 200.0f,200.0f });
        text->setText("hello\nworld!");
        text->setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
        text->setLineSpacing(-0.1f);

        RenderableManager::ref().addRenderable("Text", text);
    }

    void onTick() override 
    {
        using namespace vine;

        framebuffer_->bind();
        Renderer::ref().clear();
        Renderer::ref().beginScene();
        RenderableManager::ref().render();
        Renderer::ref().endScene();
        framebuffer_->unbind();

        Renderer::ref().clear();
        Renderer::ref().beginScene();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 1280.0f / 2.0f, 720.0f / 2.0f, 10 }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), { 1280.0f, 720.0f, 1.0f });
        Renderer::ref().drawQuad(transform, framebuffer_);
        Renderer::ref().endScene();
    }

    void onShutdown() override 
    {
    }

private:
    vine::FramebufferRef framebuffer_ = nullptr;
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    ApplicationCreationSettings settings;
    settings.windowProps = { "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };
    return new MyApp(settings);
}