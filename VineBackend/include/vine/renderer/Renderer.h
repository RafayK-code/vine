#pragma once

#include <vine/renderer/OrthographicCamera.h>

namespace vine
{
    class Renderer
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void drawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
    };
}