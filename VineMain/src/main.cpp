#include <SDL.h>

#include <Vine.h>
#include <vine/renderer/backend/Framebuffer.h>

#include <glm/gtc/matrix_transform.hpp>

//#define DEMO_FRAMEBUFFER

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

#ifdef DEMO_FRAMEBUFFER
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

        getWindow()->addEventCallback<WindowResizeEvent>([this](WindowResizeEvent& e) {
            framebuffer_->resize(e.getWidth(), e.getHeight());
        });

#endif

        /*
        RenderableManager::ref().createSpritesFromSheet("assets/spritesheets/demo/sheet.xml");
        Renderable* s = RenderableManager::ref().getRenderable("wall_texture_gold.png");

        s->setPosition({ 200.0f, 200.0f });
        s->setScale({ 100.0f, 100.0f });

        Renderable* s2 = s->clone();
        s2->setPosition({ 400.0f, 200.0f });
        s2->setScale({150.0f, 150.0f});
        RenderableManager::ref().addRenderable("Sprite2", s2);
        */

        quad_ = createRef<Quad>(RenderableState());
        quad_->setPosition({ 400.0f, 500.0f });
        quad_->setScale({ 100.0f, 100.0f });
        quad_->setColor({ 1.0f, 0.0f, 0.0f, 0.7f });
        //RenderableManager::ref().addRenderable("Quad", quad);

        quad2_ = quad_->clone().dynamicCast<Quad>();
        quad2_->setPosition({ 400.0f, 200.0f });

        text_ = createRef<Text>("assets/fonts/opensans/OpenSans-Regular.ttf", TextState());
        text_->setPosition({ 200.0f, 400.0f });
        text_->setLayer(Layer::Background);
        text_->setScale({ 50.0f, 50.0f });
        text_->setText("hello\nWorld!");
        text_->setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
        text_->setLineSpacing(0.0f);
        text_->setVisible(false);

        text2_ = text_->clone().dynamicCast<Text>();
        text2_->setPosition({ 200.0f, 200.0f });
        text2_->setText("welcome");
        text2_->setVisible(true);
    }

    void onTick(float dt) override 
    {
        using namespace vine;

        elapsedTime_ += dt * direction_;
        if (elapsedTime_ > duration_ || elapsedTime_ < 0.0f)
        {
            direction_ *= -1; // Reverse direction
            elapsedTime_ = vine::Math::clamp(elapsedTime_, 0.0f, duration_);
        }

        float easedX = easing::Elastic::easeInOut(elapsedTime_, startX_, endX_ - startX_, duration_);
        quad_->setPosition({ easedX, 500.0f });

#ifdef DEMO_FRAMEBUFFER
        framebuffer_->bind();
#endif
        Renderer::ref().clear();
        Renderer::ref().beginScene();
        RenderableManager::ref().render();
        Renderer::ref().endScene();
#ifdef DEMO_FRAMEBUFFER
        framebuffer_->unbind();
#endif

#ifdef DEMO_FRAMEBUFFER
        glDisable(GL_BLEND);
        Renderer::ref().clear();
        Renderer::ref().beginScene();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 1280.0f / 2.0f, 720.0f / 2.0f, 10 }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), { 1280.0f, 720.0f, 1.0f });
        Renderer::ref().drawQuad(transform, framebuffer_);
        Renderer::ref().endScene();
#endif
    }

    void onShutdown() override 
    {
    }

private:
    vine::FramebufferRef framebuffer_ = nullptr;
    vine::Ref<vine::Quad> quad_;
    vine::Ref<vine::Quad> quad2_;
    vine::Ref<vine::Text> text_;
    vine::Ref<vine::Text> text2_;

    float startX_ = 800.0f;
    float endX_ = 400.0f;
    float duration_ = 2.5f;
    float elapsedTime_ = 0.0f;
    int direction_ = 1; // Move right initially
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    ApplicationCreationSettings settings;
    settings.windowProps = { "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };
    return new MyApp(settings);
}