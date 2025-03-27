#include <SDL.h>

#include <Vine.h>
#include <vine/renderer/backend/Framebuffer.h>

#include <glm/gtc/matrix_transform.hpp>

class Button : public vine::Interactive
{
public:
    Button() {}
    ~Button() {}

    void onMouseDown() override
    {
        DBG_INFO("Mouse button down!");
        quad->setColor({ 0.6f, 0.0f, 0.0f, 1.0f });
    }

    void onMouseUp() override
    {
        DBG_INFO("Mouse button up!");
        quad->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    }

    void onHover() override
    {
        DBG_INFO("mouse hover!");
    }

    void onHoverExit() override
    {
        DBG_INFO("mouse hover exit!");
    }

    vine::Ref<vine::Quad> quad;
};

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
        quad_ = builder.setPosition({ 0.0f, 0.0f }).setScale({ 100.0f, 100.0f }).setColor({ 1.0f, 0.0f, 0.0f, 0.7f }).createT();
        quad2_ = builder.setPosition({ 400.0f, 200.0f }).setColor({1.0f, 0.0f, 0.0f, 1.0f}).createT();

        //quad_->setRotation(45.0f);
        //quad2_->setPivot({ 0.0f, 0.0f });
        Rect rect;
        rect.w = 100.0f;
        rect.h = 100.0f;
        rect.centerAt({ 400.0f, 200.0f });
        button_.setHitbox(rect);
        button_.quad = quad2_;

        //RenderableManager::ref().addRenderable("Quad", quad);
        gameCamera_ = new OrthographicCamera();
        RenderableManager::ref().getLayer(Layer::Background)->setCamera(gameCamera_);
        RenderableManager::ref().getLayer(Layer::CG)->setCamera(gameCamera_);
        RenderableManager::ref().getLayer(Layer::Game)->setCamera(gameCamera_);
        RenderableManager::ref().getLayer(Layer::Foreground)->setCamera(gameCamera_);

        InteractiveManager::ref().getLayer(Layer::Background)->setCamera(gameCamera_);
        InteractiveManager::ref().getLayer(Layer::CG)->setCamera(gameCamera_);
        InteractiveManager::ref().getLayer(Layer::Game)->setCamera(gameCamera_);
        InteractiveManager::ref().getLayer(Layer::Foreground)->setCamera(gameCamera_);

        setupEventCallbacks();

        TextRenderableBuilder tBuilder("assets/fonts/opensans/OpenSans-Regular.ttf");
        text_ = tBuilder
            .setPosition({ 0.0f, 0.0f }).setLayer(Layer::UI).setScale({ 4.0f, 4.0f }).setText("He")
            .setColor({ 0.0f, 1.0f, 0.0f, 1.0f }).createT();

        text3_ = tBuilder.setScale({ 30.0f, 30.0f }).setColor({ 1.0f, 1.0f, 0.0f, 1.0f }).setLayer(Layer::Background).createT();
        text3_->setPivot({ 0.5f, 0.5f });
        text_->setPivot({ 0.0f, 0.0f });

        quad3_ = builder.setPosition({ 850.0f, 500.0f }).setScale({ 100.0f, 100.0f }).setColor({0.0f, 0.5f, 0.8f, 0.6f}).createT();
        quad3_->setPriority(1.0f);
        quad3_->setPivot({ 0.5f, 0.5f });

        //quad4_ = builder.createT();

        text2_ = tBuilder.setPosition({ 850.0f, 500.0f }).setText(typedText_).setScale({ 20.0f, 20.0f }).setLayer(Layer::Game).createT();
        text2_->setKerning(0.0f);
        text2_->setLineSpacing(0.0f);
        text2_->setPivot({ 0.5f, 0.5f });
        text2_->setAlignmemnt(TextAlignment::Centered);

        quad_->setPivot({ 0.5f, 0.5f });

        TweenTarget* target = new RenderableTweenTarget(quad3_);
        TweenConfig config;
        config
            //.rotation(45.0f)
            .scale({ 150.0f, 150.0f })
            .setEase(easing::Linear::easeNone);

        TweenConfig config2;
        config2
            .color(Color(1.0f, 0.0f, 1.0f, 0.7f))
            .setEase(easing::Quadratic::easeInOut);

        tween_ = new Tween(target, duration_, config);
        //tween2_ = new Tween(target, duration_, config2);
        //tween_->play();

        TweenChainConfig config3;
        config3
            .setLoopType(TweenLoopType::PingPong)
            .setIterations(-1);

        chain_ = new TweenChain(config3);
        chain_->append(tween_);
        //chain_->append(tween2_);

        chain_->play();

        SDL_StopTextInput();

        dynamic_cast<KeyboardMouseController*>(getController())->setState(KeyboardMouseController::State::Typing);
    }

    void onTick(float dt) override 
    {
        using namespace vine;

        chain_->tick(dt);

        //quad3_->setPosition()

        Renderer::ref().setClearColor({ 0.0f, 0.3f, 0.4f, 1.0f });
        RenderableManager::ref().render();
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

                Vec3 v = gameCamera_->getPosition();
                Vec3 newPos = v - Vec3(delta, 0.0f);
                gameCamera_->setPosition(newPos);
                //DBG_INFO("NewPos: x={0}, y={1}", newPos.x, newPos.y);

                startPos.x = e.getX();
                startPos.y = e.getY();
            }
        });

        listener_.listen<MouseButtonDownEvent>(con, [this](const MouseButtonDownEvent& e) {
            //DBG_INFO("Mouse down");
            startPos.x = e.getX();
            startPos.y = e.getY();
            mouseHeld = true;
        });

        listener_.listen<MouseButtonUpEvent>(con, [this](const MouseButtonUpEvent& e) {
            //DBG_INFO("Mouse unheld");
            mouseHeld = false;
        });

        listener_.listen<MouseScrolledEvent>(con, [this](const MouseScrolledEvent& e) {
            //DBG_INFO("Mouse scrolled: {0} | {1}", e.getXOffset(), e.getYOffset());

            curZoom_ += 0.05f * e.getYOffset();
            curZoom_ = Math::clamp(curZoom_, 0.50f, 2.0f);

            gameCamera_->setZoom(curZoom_);
        });
    }

private:
    vine::FramebufferRef framebuffer_ = nullptr;

    vine::Ref<vine::Quad> quad_;
    vine::Ref<vine::Quad> quad2_;
    vine::Ref<vine::Quad> quad3_;
    vine::Ref<vine::Quad> quad4_;

    vine::Ref<vine::Text> text_;
    vine::Ref<vine::Text> text2_;
    vine::Ref<vine::Text> text3_;

    vine::Tween* tween_;
    vine::Tween* tween2_;

    vine::EventListener listener_;

    vine::TweenChain* chain_;
    float duration_ = 2.5f;

    std::string typedText_;

    vine::Vec2 startPos = { 0.0f, 0.0f };
    bool mouseHeld = false;

    float curZoom_ = 1.0f;

    vine::Ref<vine::OrthographicCamera> gameCamera_;
    Button button_;
};

vine::Application* vine::createApplication(int argc, char** argv)
{
    ApplicationCreationSettings settings;
    settings.windowProps = { "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720 };
    return new MyApp(settings);
}