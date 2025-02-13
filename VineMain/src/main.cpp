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

        QuadRenderableBuilder builder;
        quad_ = builder.setPosition({ 400.0f, 500.0f }).setScale({ 100.0f, 100.0f }).setColor({ 1.0f, 0.0f, 0.0f, 0.7f }).createT();
        quad2_ = builder.setPosition({ 400.0f, 200.0f }).createT();

        //RenderableManager::ref().addRenderable("Quad", quad);

        Renderer::ref().getCamera().setPosition({ 640, 360, 0.0f });

        setupEventCallbacks();

        TextRenderableBuilder tBuilder("assets/fonts/opensans/OpenSans-Regular.ttf");
        text_ = tBuilder
            .setPosition({ 850.0f, 500.0f }).setLayer(Layer::Background).setScale({ 200.0f, 200.0f }).setText("Hello\nWorld!")
            .setColor({ 0.0f, 1.0f, 0.0f, 1.0f }).createT();

        quad3_ = builder.setPosition({ 850.0f, 500.0f }).setScale({ 30.0f, 30.0f }).setColor({0.0f, 1.0f, 0.0f, 1.0f}).createT();
        quad3_->setPriority(1.0f);
        text2_ = tBuilder.setPosition({ 200.0f, 200.0f }).setText(typedText_).createT();

        TweenTarget* target = new RenderableTweenTarget(quad_);
        TweenConfig config;
        config
            .position(Vec2(800.0f, 500.0f))
            .scale(Vec2(200.0f, 200.0f))
            .setEase(easing::Bounce::easeOut);

        TweenConfig config2;
        config2
            .color(Color(1.0f, 0.0f, 1.0f, 0.7f))
            .setEase(easing::Quadratic::easeInOut);

        tween_ = new Tween(target, duration_, config);
        tween2_ = new Tween(target, duration_, config2);
        //tween_->play();

        TweenChainConfig config3;
        config3
            .setLoopType(TweenLoopType::PingPong)
            .setIterations(-1);

        chain_ = new TweenChain(config3);
        chain_->append(tween_);
        chain_->append(tween2_);

        chain_->play();

        SDL_StopTextInput();

        dynamic_cast<KeyboardMouseController*>(getController())->setState(KeyboardMouseController::State::Typing);
    }

    void onTick(float dt) override 
    {
        using namespace vine;

        chain_->tick(dt);

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
        delete chain_;
    }

private:
    void setupEventCallbacks()
    {
        using namespace vine;

        Controller& con = *getController();

        listener_.listen<KeyTypedEvent>(con, [this](const KeyTypedEvent& e) {
            DBG_INFO("Key typed text: {0}", e.getText());
            typedText_ += e.getText();
            text2_->setText(typedText_);
        });

        listener_.listen<KeyDownEvent>(con, [this](const KeyDownEvent& e) {
            DBG_INFO("Key down: {0}, {1}", e.getKeyCode(), e.getThisEventTypeID());
            if (e.getKeyCode() == Key::Backspace)
            {
                if (!typedText_.empty())
                    typedText_.pop_back();
                text2_->setText(typedText_);
            }
            else if (e.getKeyCode() == Key::Enter)
            {
                typedText_ += '\n';
                text2_->setText(typedText_);
            }
        });

        listener_.listen<KeyHeldEvent>(con, [this](const KeyHeldEvent& e) {
            DBG_INFO("Key down: {0}", e.getKeyCode());
            if (e.getKeyCode() == Key::Backspace)
            {
                if (!typedText_.empty())
                    typedText_.pop_back();
                text2_->setText(typedText_);
            }
        });

        listener_.listen<MouseMovedEvent>(con, [this](const MouseMovedEvent& e) {
            if (mouseHeld)
            {
                Vec2 delta = Vec2(e.getX() - startPos.x, startPos.y - e.getY()) / curZoom_;

                Vec3 v = Renderer::ref().getCamera().getPosition();
                Vec3 newPos = v - Vec3(delta, 0.0f);
                Renderer::ref().getCamera().setPosition(newPos);
                DBG_INFO("NewPos: x={0}, y={1}", newPos.x, newPos.y);

                startPos.x = e.getX();
                startPos.y = e.getY();
            }
        });

        listener_.listen<MouseButtonDownEvent>(con, [this](const MouseButtonDownEvent& e) {
            DBG_INFO("Mouse down");
            startPos.x = e.getX();
            startPos.y = e.getY();
            mouseHeld = true;
        });

        listener_.listen<MouseButtonUpEvent>(con, [this](const MouseButtonUpEvent& e) {
            DBG_INFO("Mouse unheld");
            mouseHeld = false;
        });

        listener_.listen<MouseScrolledEvent>(con, [this](const MouseScrolledEvent& e) {
            DBG_INFO("Mouse scrolled: {0} | {1}", e.getXOffset(), e.getYOffset());

            curZoom_ += 0.05f * e.getYOffset();
            curZoom_ = Math::clamp(curZoom_, 0.50f, 2.0f);

            Renderer::ref().getCamera().setZoom(curZoom_);
        });
    }

private:
    vine::FramebufferRef framebuffer_ = nullptr;

    vine::Ref<vine::Quad> quad_;
    vine::Ref<vine::Quad> quad2_;
    vine::Ref<vine::Quad> quad3_;

    vine::Ref<vine::Text> text_;
    vine::Ref<vine::Text> text2_;

    vine::Tween* tween_;
    vine::Tween* tween2_;

    vine::EventListener listener_;

    vine::TweenChain* chain_;
    float duration_ = 2.5f;

    std::string typedText_;

    vine::Vec2 startPos = { 0.0f, 0.0f };
    bool mouseHeld = false;

    float curZoom_ = 1.0f;
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    ApplicationCreationSettings settings;
    settings.windowProps = { "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };
    return new MyApp(settings);
}