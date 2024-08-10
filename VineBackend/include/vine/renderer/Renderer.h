#pragma once

#include <vine/renderer/OrthographicCamera.h>
#include <vine/renderer/backend/Texture.h>
#include <vine/util/Singleton.h>
#include <vine/renderer/backend/VertexArray.h>
#include <vine/renderer/backend/ShaderCache.h>
#include <vine/renderer/GraphicsContext.h>

#include <array>

namespace vine
{
    class Renderer : public Singleton<Renderer>
    {
        friend class Singleton<Renderer>;
    public:
        ~Renderer();

        static void init(SDL_Window* window);
        static void shutdown();

        void setClearColor(const glm::vec4& color);
        void clear();
        
        void beginScene(const OrthographicCamera& camera);
        void endScene();
        void flush();
        
        void drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
        void drawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
        
        void drawQuad(const glm::vec2& position, const glm::vec2& scale, const TextureRef& texture);
        void drawQuad(const glm::vec3& position, const glm::vec2& scale, const TextureRef& texture);
        
        void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        void drawQuad(const glm::mat4& transform, const TextureRef& texture, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

    private:
        Renderer(SDL_Window* window);

        void startBatch();
        void nextBatch();

    private:
        struct QuadVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 texCoord;
            float texIndex;
        };

        struct RendererData
        {
            const uint32_t maxQuads = 10000;
            const uint32_t maxVertices = maxQuads * 4;
            const uint32_t maxIndices = maxQuads * 6;
            static const uint32_t maxTextureSlots = 32;

            uint32_t quadIndexCount = 0;

            VertexBufferRef quadVB;
            VertexArrayRef quadVertexArray;
            ShaderRef flatColorShader;
            ShaderRef textureShader;

            TextureRef whiteTexture;

            QuadVertex* quadVertexBufferBase = nullptr;
            QuadVertex* quadVertexBufferPtr = nullptr;

            std::array<TextureRef, maxTextureSlots> textureSlots;
            uint32_t textureSlotIndex = 1;

            glm::vec4 quadVertexPositions[4];

            ~RendererData() { delete[] quadVertexBufferBase; }
        };

        std::unique_ptr<RendererData> data_;
        GraphicsContext context_;
    };
}