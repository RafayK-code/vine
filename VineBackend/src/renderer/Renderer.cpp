#include <vine/renderer/Renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace vine
{
    Renderer::Renderer()
    {
        data_ = std::make_unique<RendererData>();
        data_->quadVertexArray = createVertexArray();;

        data_->quadVB = createVertexBuffer(data_->maxQuads * sizeof(QuadVertex));
        data_->quadVB->setLayout({
            { "a_Position", ShaderDataType::Float3 },
            { "a_Color", ShaderDataType::Float4 },
            { "a_TexCoord", ShaderDataType::Float2 },
            { "a_TexIndex", ShaderDataType::Float }
            });
        data_->quadVertexArray->addVertexBuffer(data_->quadVB);

        data_->quadVertexBufferBase = new QuadVertex[data_->maxVertices];

        uint32_t* quadIndices = new uint32_t[data_->maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < data_->maxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        IndexBufferRef quadIB = createIndexBuffer(quadIndices, data_->maxIndices);
        data_->quadVertexArray->setIndexBuffer(quadIB);

        delete[] quadIndices;

        //texture stuff
        data_->whiteTexture = createTexture(TextureSpecification());
        uint32_t whiteTextureData = 0xffffffff;
        data_->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        data_->textureSlots[0] = data_->whiteTexture;

        int32_t samplers[RendererData::maxTextureSlots];
        for (int i = 0; i < RendererData::maxTextureSlots; i++)
            samplers[i] = i;

        data_->quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        data_->quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        data_->quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
        data_->quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

        // shader stuff
        ShaderCache::init();
        data_->textureShader = ShaderCache::ref().load("TextureShader", "assets/shaders/texture.vs", "assets/shaders/texture.fs");
        data_->textureShader->bind();
        data_->textureShader->uploadUniformIntArray("u_Textures", samplers, data_->maxTextureSlots);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::init()
    {
        createSingleton();
    }

    void Renderer::shutdown()
    {
        destroySingleton();
    }

    void Renderer::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::beginScene(const OrthographicCamera& camera)
    {
        //data_->flatColorShader->bind();
        //data_->flatColorShader->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());

        data_->textureShader->bind();
        data_->textureShader->uploadUniformMat4("u_ViewProjection", camera.getProjectionMatrix());

        data_->quadIndexCount = 0;
        data_->quadVertexBufferPtr = data_->quadVertexBufferBase;

        data_->textureSlotIndex = 1;
    }

    void Renderer::endScene()
    {
        uint32_t size = (uint8_t*)data_->quadVertexBufferPtr - (uint8_t*)data_->quadVertexBufferBase;
        data_->quadVB->setData(data_->quadVertexBufferBase, size);

        flush();
    }

    void Renderer::flush()
    {
        for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
        {
            data_->textureSlots[i]->bind(i);
        }
        glDrawElements(GL_TRIANGLES, data_->quadIndexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
    {
        drawQuad({ position.x, position.y, 0.0f }, scale, color);
    }

    void Renderer::drawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
    {
        data_->quadVertexBufferPtr->position = position;
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
        data_->quadVertexBufferPtr->texIndex = 0.0f;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x + scale.x, position.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
        data_->quadVertexBufferPtr->texIndex = 0.0f;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x + scale.x, position.y + scale.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
        data_->quadVertexBufferPtr->texIndex = 0.0f;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x, position.y + scale.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
        data_->quadVertexBufferPtr->texIndex = 0.0f;
        data_->quadVertexBufferPtr++;

        data_->quadIndexCount += 6;

        /*
        data_->flatColorShader->bind();
        data_->flatColorShader->uploadUniformFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
        data_->flatColorShader->uploadUniformMat4("u_Transform", transform);

        data_->quadVertexArray->bind();
        glDrawElements(GL_TRIANGLES, data_->quadVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
        */
    }

    void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const TextureRef& texture)
    {
        drawQuad({ position.x, position.y, 0.0f }, scale, texture);
    }

    void Renderer::drawQuad(const glm::vec3& position, const glm::vec2& scale, const TextureRef& texture)
    {
        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
        {
            if (*data_->textureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)data_->textureSlotIndex;
            data_->textureSlots[data_->textureSlotIndex] = texture;
            data_->textureSlotIndex++;
        }

        data_->quadVertexBufferPtr->position = position;
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 0.0f, 0.0f };
        data_->quadVertexBufferPtr->texIndex = textureIndex;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x + scale.x, position.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 1.0f, 0.0f };
        data_->quadVertexBufferPtr->texIndex = textureIndex;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x + scale.x, position.y + scale.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 1.0f, 1.0f };
        data_->quadVertexBufferPtr->texIndex = textureIndex;
        data_->quadVertexBufferPtr++;

        data_->quadVertexBufferPtr->position = { position.x, position.y + scale.y, position.z };
        data_->quadVertexBufferPtr->color = color;
        data_->quadVertexBufferPtr->texCoord = { 0.0f, 1.0f };
        data_->quadVertexBufferPtr->texIndex = textureIndex;
        data_->quadVertexBufferPtr++;

        data_->quadIndexCount += 6;

        /*
        data_->textureShader->bind();
        data_->textureShader->uploadUniformInt("u_Texture", 0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
        data_->textureShader->uploadUniformMat4("u_Transform", transform);

        texture->bind();

        data_->quadVertexArray->bind();
        glDrawElements(GL_TRIANGLES, data_->quadVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
        */
    }
    void Renderer::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f;
        constexpr glm::vec2 texCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            data_->quadVertexBufferPtr->position = transform * data_->quadVertexPositions[i];
            data_->quadVertexBufferPtr->color = color;
            data_->quadVertexBufferPtr->texCoord = texCoords[i];
            data_->quadVertexBufferPtr->texIndex = textureIndex;
            data_->quadVertexBufferPtr++;
        }

        data_->quadIndexCount += 6;
    }

    void Renderer::drawQuad(const glm::mat4& transform, const TextureRef& texture, const glm::vec4& tintColor)
    {
        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec2 texCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
        {
            if (*data_->textureSlots[i] == *texture)
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)data_->textureSlotIndex;
            data_->textureSlots[data_->textureSlotIndex] = texture;
            data_->textureSlotIndex++;
        }

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            data_->quadVertexBufferPtr->position = transform * data_->quadVertexPositions[i];
            data_->quadVertexBufferPtr->color = tintColor;
            data_->quadVertexBufferPtr->texCoord = texCoords[i];
            data_->quadVertexBufferPtr->texIndex = textureIndex;
            data_->quadVertexBufferPtr++;
        }

        data_->quadIndexCount += 6;
    }
}