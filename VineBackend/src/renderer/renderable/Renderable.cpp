#include <vine/renderer/renderable/Renderable.h>

#include <vine/renderer/renderable/RenderableManager.h>
#include <vine/renderer/backend/ShaderCache.h>

#include <glm/gtc/matrix_transform.hpp>

namespace vine
{
    namespace Layer
    {
        bool isValidLayer(RenderableLayerLevel layer)
        {
            return layer >= 1 && layer <= 6;
        }
    }

    Renderable::Renderable(const RenderableState& state)
        : state_(state)
    {
        RenderableManager::ref().getLayer(state_.layer)->add(this);
        updateTransform();
    }

    Renderable::~Renderable()
    {
        RenderableManager::ref().getLayer(state_.layer)->remove(this);
    }

    Renderable::Renderable(const Renderable& other)
        : state_(other.state_), transform_(other.transform_), shader_(other.shader_), shaderName_(other.shaderName_)
    {
        RenderableManager::ref().getLayer(state_.layer)->add(this);
    }

    void Renderable::setLayer(RenderableLayerLevel layer)
    {
        RenderableManager::ref().getLayer(state_.layer)->remove(this);
        state_.layer = layer;
        RenderableManager::ref().getLayer(state_.layer)->add(this);
        updateTransform();
    }

    void Renderable::setShader(const std::string& name)
    {
        shaderName_ = name;
        shader_ = ShaderCache::ref().get(name);
    }

    void Renderable::updateTransform()
    {
        transform_ = glm::translate(glm::mat4(1.0f), { state_.pos.x, state_.pos.y, state_.layer * 100 + state_.priority }) *
            glm::rotate(glm::mat4(1.0f), glm::radians(state_.rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), { state_.scale.x, state_.scale.y, 1.0f });
    }
}