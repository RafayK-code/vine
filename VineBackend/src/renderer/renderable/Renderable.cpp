#include <vine/renderer/renderable/Renderable.h>

#include <vine/renderer/backend/ShaderCache.h>

#include <glm/gtc/matrix_transform.hpp>

namespace vine
{
    Renderable::Renderable(const RenderableState& state)
        : state_(state)
    {
        updateTransform();
    }

    Renderable::~Renderable()
    {
    }

    void Renderable::setShader(const std::string& name)
    {
        shaderName_ = name;
        shader_ = ShaderCache::ref().get(name);
    }

    void Renderable::updateTransform()
    {
        transform_ = glm::translate(glm::mat4(1.0f), { state_.pos.x, state_.pos.y, state_.layer }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(state_.rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), { state_.scale.x, state_.scale.y, 1.0f });
    }
}