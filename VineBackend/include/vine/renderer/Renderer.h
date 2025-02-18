#pragma once

#include <vine/renderer/OrthographicCamera.h>
#include <vine/renderer/backend/Texture.h>
#include <vine/util/Singleton.h>
#include <vine/renderer/backend/VertexArray.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/backend/Framebuffer.h>
#include <vine/renderer/GraphicsContext.h>
#include <vine/renderer/backend/Font.h>
#include <vine/window/Window.h>
#include <vine/resource/ResourceImage.h>
#include <vine/resource/ResourceFont.h>

#include <array>
#include <string>
#include <variant>

namespace vine
{
    class Renderer : public Singleton<Renderer>
    {
        friend class Singleton<Renderer>;
    public:
        ~Renderer();

        static void init(Window* window);
        static void shutdown();

        void setViewport(const glm::vec4& dimensions);
        void setClearColor(const glm::vec4& color);

        const glm::mat4& getOrtho() const { return projectionMatrix_; }
        void setOrtho(float left, float right, float bottom, float top, float zNear, float zFar);

        const Ref<OrthographicCamera> getActiveCamera() const { return camera_; }
        void setActiveCamera(const Ref<OrthographicCamera>& camera);

        void clear();
        
        void beginScene(const Ref<OrthographicCamera>& camera);
        void endScene();

        void startBatch();
        void nextBatch();

        void flush();
        
        /*
        void drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
        void drawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
        
        void drawQuad(const glm::vec2& position, const glm::vec2& scale, const TextureRef& texture, glm::vec2 texPos = { -1.0f, -1.0f }, glm::vec2 texScale = { -1.0f, -1.0f });
        void drawQuad(const glm::vec3& position, const glm::vec2& scale, const TextureRef& texture, glm::vec2 texPos = { -1.0f, -1.0f }, glm::vec2 texScale = { -1.0f, -1.0f });
        */

        void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        void drawQuad(const glm::mat4& transform, const Ref<ResourceImage>& texture, const glm::vec2& texPos = { -1.0f, -1.0f }, const glm::vec2& texScale = { -1.0f, -1.0f }, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
        void drawQuad(const glm::mat4& transform, const FramebufferRef& framebuffer, const glm::vec2& texPos = { -1.0f, -1.0f }, const glm::vec2& texScale = { -1.0f, -1.0f }, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

        struct TextParams
        {
            glm::vec4 color = { 1.0f, 1.0f, 1.0, 1.0 };
            float kerning = 0.0f;
            float lineSpacing = 0.0f;
        };

        void drawText(const std::string& text, const Ref<ResourceFont>& font, const glm::mat4& trnasform, const TextParams& params);

        ShaderRef getActiveQuadShader() const { return data_->quadShader; }
        ShaderRef getActiveTextShader() const { return data_->textShader; }

        void setActiveQuadShader(const std::string& shader, const std::string& vs, const std::string& fs);
        void setActiveQuadShader(const ShaderRef& shader);

        void setActiveTextShader(const std::string& shader, const std::string& vs, const std::string& fs);
        void setActiveTextShader(const ShaderRef& shader);

    private:
        Renderer(Window* window);

    private:
        struct QuadVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 texCoord;
            float texIndex;
        };

        struct TextVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 texCoord;
        };

        using RenderTexture = std::variant<Ref<ResourceImage>, FramebufferRef>;

        struct RendererData
        {
            const uint32_t maxQuads = 10000;
            const uint32_t maxVertices = maxQuads * 4;
            const uint32_t maxIndices = maxQuads * 6;
            static const uint32_t maxTextureSlots = 32;

            VertexBufferRef quadVB;
            VertexArrayRef quadVertexArray;
            ShaderRef flatColorShader;
            ShaderRef quadShader;

            VertexBufferRef textVB;
            VertexArrayRef textVertexArray;
            ShaderRef textShader;

            uint32_t quadIndexCount = 0;
            QuadVertex* quadVertexBufferBase = nullptr;
            QuadVertex* quadVertexBufferPtr = nullptr;

            uint32_t textIndexCount = 0;
            TextVertex* textVertexBufferBase = nullptr;
            TextVertex* textVertexBufferPtr = nullptr;

            Ref<ResourceImage> whiteTexture;
            std::array<RenderTexture, maxTextureSlots> textureSlots;
            uint32_t textureSlotIndex = 1;

            glm::vec4 quadVertexPositions[4];

            Ref<ResourceImage> fontAtlasTexture;

            ~RendererData() { delete[] quadVertexBufferBase; }
        };

        std::unique_ptr<RendererData> data_;
        GraphicsContext context_;

        glm::mat4 projectionMatrix_;
        Ref<OrthographicCamera> camera_;
    };
}