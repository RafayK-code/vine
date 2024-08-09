#include <vine/renderer/Renderer.h>

#include <vine/renderer/backend/VertexArray.h>
#include <vine/renderer/backend/Shader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace vine
{
    struct RendererStorage
    {
        RefPtr<VertexArray> quadVertexArray;
        RefPtr<Shader> flatColorShader;
    };

    static RendererStorage* data;

    void Renderer::init()
    {
        data = new RendererStorage;
        data->quadVertexArray = makeRef<VertexArray>();

        float squareVertices[5 * 4] = 
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };

        RefPtr<VertexBuffer> squareVB = makeRef<VertexBuffer>(squareVertices, sizeof(squareVertices));
        squareVB->setLayout({
            { "a_Position", ShaderDataType::Float3 }
        });
        data->quadVertexArray->addVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        RefPtr<IndexBuffer> squareIB = makeRef<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        data->quadVertexArray->setIndexBuffer(squareIB);

        data->flatColorShader = makeRef<Shader>("BaseShader", "assets/shaders/flat_color.vs", "assets/shaders/flat_color.fs");
    }

    void Renderer::shutdown()
    {
        delete data;
    }

    void Renderer::beginScene(const OrthographicCamera& camera)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer::endScene()
    {

    }

    void Renderer::drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
    {
        drawQuad({ position.x, position.y, 0.0f }, scale, color);
    }

    void Renderer::drawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
    {
        data->flatColorShader->bind();
        data->flatColorShader->uploadUniformFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
        data->flatColorShader->uploadUniformMat4("u_Transform", transform);

        data->quadVertexArray->bind();
        glDrawElements(GL_TRIANGLES, data->quadVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
}