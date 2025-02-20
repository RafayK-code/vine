#include <vine/renderer/Renderer.h>

#include <vine/renderer/backend/MSDFData.h>
#include <vine/core/Logger.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace vine
{
    Renderer::Renderer(Window* window)
        : projectionMatrix_(glm::ortho(0.0f, (float)window->getWidth(), 0.0f, (float)window->getHeight(), 0.0f, -1000.0f))
    {
        context_.createContext(window);

        data_ = std::make_unique<RendererData>();

        //quad stuff
        data_->quadVertexArray = createVertexArray();

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

        //text stuff
        data_->textVertexArray = createVertexArray();

        data_->textVB = createVertexBuffer(data_->maxVertices * sizeof(TextVertex));
        data_->textVB->setLayout({
            { "a_Position", ShaderDataType::Float3 },
            { "a_Color", ShaderDataType::Float4 },
            { "a_TexCoord", ShaderDataType::Float2 }
        });
        data_->textVertexArray->addVertexBuffer(data_->textVB);
        data_->textVertexArray->setIndexBuffer(quadIB);
        data_->textVertexBufferBase = new TextVertex[data_->maxVertices];


        //texture stuff
        data_->whiteTexture = ResourceImage::createBuiltinWhite();

        data_->textureSlots[0] = data_->whiteTexture;

        int32_t samplers[RendererData::maxTextureSlots];
        for (int i = 0; i < RendererData::maxTextureSlots; i++)
            samplers[i] = i;

        data_->quadVertexPositions[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
        data_->quadVertexPositions[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
        data_->quadVertexPositions[2] = { 1.0f,  1.0f, 0.0f, 1.0f };
        data_->quadVertexPositions[3] = { 0.0f,  1.0f, 0.0f, 1.0f };

        // shader stuff
        ShaderCache::init();
        data_->quadShader = ShaderCache::ref().load("QuadShader", "assets/shaders/texture.vs", "assets/shaders/texture.fs");
        data_->quadShader->bind();
        data_->quadShader->uploadUniformIntArray("u_Textures", samplers, data_->maxTextureSlots);

        data_->textShader = ShaderCache::ref().load("TextShader", "assets/shaders/text.vs", "assets/shaders/text.fs");

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glDisable(GL_BLEND);
    }

    Renderer::~Renderer()
    {
        context_.destroyContext();
    }

    void Renderer::init(Window* window)
    {
        getHiddenPtr() = new Renderer(window);
        getHiddenPtr()->initStatics();
    }

    void Renderer::shutdown()
    {
        destroySingleton();
    }

    void Renderer::setViewport(const glm::vec4& dimensions)
    {
        glViewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
    }

    void Renderer::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::setOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
    {
        projectionMatrix_ = glm::ortho(left, right, bottom, top, zNear, zFar);
    }

    void Renderer::setActiveCamera(const Ref<OrthographicCamera>& camera)
    {
        camera_ = camera;

        glm::mat4 viewMatrix = camera ? camera->getViewMatrix() : glm::mat4(1.0f);
        glm::mat4 viewProjectionMatrix = projectionMatrix_ * viewMatrix;
        data_->quadShader->bind();
        data_->quadShader->uploadUniformMat4("u_ViewProjection", viewProjectionMatrix);

        data_->textShader->bind();
        data_->textShader->uploadUniformMat4("u_ViewProjection", viewProjectionMatrix);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::beginScene(const Ref<OrthographicCamera>& camera)
    {
        glm::mat4 viewMatrix = camera ? camera->getViewMatrix() : glm::mat4(1.0f);
        glm::mat4 viewProjectionMatrix = projectionMatrix_ * viewMatrix;
        data_->quadShader->bind();
        data_->quadShader->uploadUniformMat4("u_ViewProjection", viewProjectionMatrix);

        data_->textShader->bind();
        data_->textShader->uploadUniformMat4("u_ViewProjection", viewProjectionMatrix);

        startBatch();
    }

    void Renderer::endScene()
    {
        flush();
    }

    void Renderer::flush()
    {
        if (data_->quadIndexCount)
        {
            uint32_t size = (uint8_t*)data_->quadVertexBufferPtr - (uint8_t*)data_->quadVertexBufferBase;
            data_->quadVB->setData(data_->quadVertexBufferBase, size);

            for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
            {
                if (Ref<ResourceImage>* tex = std::get_if<Ref<ResourceImage>>(&data_->textureSlots[i]))
                    (*tex)->bind(i);
                else if (FramebufferRef* buf = std::get_if<FramebufferRef>(&data_->textureSlots[i]))
                    (*buf)->bindToTexture(i);
            }

            data_->quadShader->bind();
            data_->quadVertexArray->bind();
            glDrawElements(GL_TRIANGLES, data_->quadIndexCount, GL_UNSIGNED_INT, nullptr);
        }

        if (data_->textIndexCount)
        {
            uint32_t size = (uint8_t*)data_->textVertexBufferPtr - (uint8_t*)data_->textVertexBufferBase;
            data_->textVB->setData(data_->textVertexBufferBase, size);

            TextVertex* buf = data_->textVertexBufferBase;
            data_->fontAtlasTexture->bind(0);
            data_->textShader->bind();
            data_->textShader->uploadUniformInt("u_FontAtlas", 0);

            data_->textVertexArray->bind();
            glDrawElements(GL_TRIANGLES, data_->textIndexCount, GL_UNSIGNED_INT, nullptr);
        }
    }

    void Renderer::startBatch()
    {
        data_->quadIndexCount = 0;
        data_->quadVertexBufferPtr = data_->quadVertexBufferBase;

        data_->textIndexCount = 0;
        data_->textVertexBufferPtr = data_->textVertexBufferBase;

        data_->textureSlotIndex = 1;
    }

    void Renderer::nextBatch()
    {
        flush();
        startBatch();
    }

    void Renderer::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f;
        constexpr glm::vec2 texCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

        if (data_->quadIndexCount >= data_->maxIndices)
            nextBatch();

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

    void Renderer::drawQuad(const glm::mat4& transform, const Ref<ResourceImage>& texture, const glm::vec2& srcPos, const glm::vec2& srcScale, const glm::vec4& tintColor)
    {
        constexpr size_t quadVertexCount = 4;
        glm::vec2 texCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

        if (srcPos.x >= 0.0f && srcPos.y >= 0.0f && srcScale.x >= 0.0f && srcScale.y >= 0.0f)
        {
            float srcXNorm = srcPos.x / (float)texture->getWidth();
            float srcYNorm = srcPos.y / (float)texture->getHeight();

            float srcWNorm = srcScale.x / (float)texture->getWidth();
            float srcHNorm = srcScale.y / (float)texture->getHeight();

            texCoords[0] = { srcXNorm, srcYNorm };
            texCoords[1] = { srcXNorm + srcWNorm, srcYNorm};
            texCoords[2] = { srcXNorm + srcWNorm, srcYNorm + srcHNorm };
            texCoords[3] = { srcXNorm, srcYNorm + srcHNorm };
        }

        if (data_->quadIndexCount >= data_->maxIndices)
            nextBatch();

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
        {
            if (Ref<ResourceImage>* tex = std::get_if<Ref<ResourceImage>>(&data_->textureSlots[i]))
            {
                if ((*tex)->getRendererID() == texture->getRendererID())
                {
                    textureIndex = (float)i;
                    break;
                }
            }
        }

        if (textureIndex == 0.0f)
        {
            if (data_->textureSlotIndex >= data_->maxTextureSlots)
                nextBatch();

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

    void Renderer::drawQuad(const glm::mat4& transform, const FramebufferRef& framebuffer, const glm::vec2& srcPos, const glm::vec2& srcScale, const glm::vec4& tintColor)
    {
        constexpr size_t quadVertexCount = 4;
        glm::vec2 texCoords[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };

        if (srcPos.x >= 0.0f && srcPos.y >= 0.0f && srcScale.x >= 0.0f && srcScale.y >= 0.0f)
        {
            float srcXNorm = srcPos.x / (float)framebuffer->getSpecification().width;
            float srcYNorm = srcPos.y / (float)framebuffer->getSpecification().height;

            float srcWNorm = srcScale.x / (float)framebuffer->getSpecification().width;
            float srcHNorm = srcScale.y / (float)framebuffer->getSpecification().height;

            texCoords[0] = { srcXNorm, srcYNorm };
            texCoords[1] = { srcXNorm + srcWNorm, srcYNorm };
            texCoords[2] = { srcXNorm + srcWNorm, srcYNorm + srcHNorm };
            texCoords[3] = { srcXNorm, srcYNorm + srcHNorm };
        }

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < data_->textureSlotIndex; i++)
        {
            if (FramebufferRef* buf = std::get_if<FramebufferRef>(&data_->textureSlots[i]))
            {
                if (**buf == *framebuffer)
                {
                    textureIndex = (float)i;
                    break;
                }
            }
        }

        if (textureIndex == 0.0f)
        {
            if (data_->textureSlotIndex >= data_->maxTextureSlots)
                nextBatch();

            textureIndex = (float)data_->textureSlotIndex;
            data_->textureSlots[data_->textureSlotIndex] = framebuffer;
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

    void Renderer::drawText(const std::string& text, const Ref<ResourceFont>& font, const glm::mat4& transform, const TextParams& params)
    {
        const msdf_atlas::FontGeometry& fontGeomtry = font->getData()->fontGeometry;
        const msdfgen::FontMetrics& metrics = fontGeomtry.getMetrics();
        Ref<ResourceImage> fontAtlas = font->getAtlasTexture();

        data_->fontAtlasTexture = fontAtlas;

        double x = 0.0;
        double fsScale = font->getFontSize() / (metrics.ascenderY - metrics.descenderY);
        double y = 0.0;

        const float spaceGlyphAdvance = fontGeomtry.getGlyph(' ')->getAdvance();

        for (size_t i = 0; i < text.size(); i++)
        {
            char character = text[i];
            if (character == '\r')
                continue;

            if (character == '\n')
            {
                x = 0;
                y -= fsScale * metrics.lineHeight + params.lineSpacing;
                continue;
            }

            if (character == ' ')
            {
                float advance = spaceGlyphAdvance;
                if (i < text.size() - 1)
                {
                    char nextCharacter = text[i + 1];
                    double dAdvance;
                    fontGeomtry.getAdvance(dAdvance, character, nextCharacter);
                    advance = (float)dAdvance;
                }

                x += fsScale * advance + params.kerning;
                continue;
            }

            if (character == '\t')
            {
                x += 4.0f * (fsScale * spaceGlyphAdvance + params.kerning);
                continue;
            }

            const msdf_atlas::GlyphGeometry* glyph = fontGeomtry.getGlyph(character);
            if (!glyph)
                glyph = fontGeomtry.getGlyph('?');

            double al, ab, ar, at;
            glyph->getQuadAtlasBounds(al, ab, ar, at);
            glm::vec2 texCoordMin = { (float)al, (float)ab };
            glm::vec2 texCoordMax = { (float)ar, (float)at };

            double pl, pb, pr, pt;
            glyph->getQuadPlaneBounds(pl, pb, pr, pt);
            glm::vec2 quadMin = { (float)pl, (float)pb };
            glm::vec2 quadMax = { (float)pr, (float)pt };

            quadMin *= fsScale;
            quadMax *= fsScale;

            quadMin -= quadMin;
            quadMax -= quadMin;

            quadMin += glm::vec2(x, y);
            quadMax += glm::vec2(x, y);

            float texelWidth = 1.0f / fontAtlas->getWidth();
            float texelHeight = 1.0f / fontAtlas->getHeight();
            texCoordMin *= glm::vec2(texelWidth, texelHeight);
            texCoordMax *= glm::vec2(texelWidth, texelHeight);

            constexpr size_t textVertexCount = 4;
            const glm::vec2 texCoords[] = { texCoordMin, {texCoordMin.x, texCoordMax.y}, texCoordMax, {texCoordMax.x, texCoordMin.y} };
            const glm::vec4 positions[] = { {quadMin, 0.0f, 1.0f}, {quadMin.x, quadMax.y, 0.0f, 1.0f}, {quadMax, 0.0f, 1.0f}, {quadMax.x, quadMin.y, 0.0f, 1.0f} };


            for (size_t i = 0; i < textVertexCount; i++)
            {
                data_->textVertexBufferPtr->position = transform * positions[i];
                data_->textVertexBufferPtr->color = params.color;
                data_->textVertexBufferPtr->texCoord = texCoords[i];
                data_->textVertexBufferPtr++;
            }

            data_->textIndexCount += 6;

            if (i < text.size() - 1)
            {
                double advance = glyph->getAdvance();
                char nextCharacter = text[i + 1];
                fontGeomtry.getAdvance(advance, character, nextCharacter);

                x += fsScale * advance + params.kerning;
            }
        }
    }

    void Renderer::setActiveQuadShader(const std::string& shader, const std::string& vs, const std::string& fs)
    {
        data_->quadShader = ShaderCache::ref().load(shader, vs, fs);
    }

    void Renderer::setActiveQuadShader(const ShaderRef& shader)
    {
        data_->quadShader = shader;
    }

    void Renderer::setActiveTextShader(const std::string& shader, const std::string& vs, const std::string& fs)
    {
        data_->textShader = ShaderCache::ref().load(shader, vs, fs);
    }

    void Renderer::setActiveTextShader(const ShaderRef& shader)
    {
        data_->textShader = shader;
    }
}