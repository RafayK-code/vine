#include <vine/renderer/renderable/Renderable.h>

#include <vine/renderer/backend/ShaderCache.h>

#include <glm/gtc/matrix_transform.hpp>

namespace vine
{
    void IRenderable::setShader(const std::string& name)
    {
        shader_ = ShaderCache::ref().get(name);
    }

    void IRenderable::updateTransform()
    {
        transform_ = glm::translate(glm::mat4(1.0f), { state_.pos.x, state_.pos.y, state_.layer }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(state_.rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), { state_.scale.x, state_.scale.y, 1.0f });
    }
}