#pragma once

#include <vine/renderer/backend/Shader.h>
#include <vine/sys/Ref.h>
#include <vine/renderer/Color.h>
#include <vine/util/Math.h>
#include <vine/core/Layer.h>

#include <glm/glm.hpp>
#include <string>

namespace vine
{
    using RenderableLayerLevel = uint32_t;

    namespace Layer
    {
        bool isValidLayer(RenderableLayerLevel layer);
    }

    struct RenderableState
    {
        glm::vec2 pos = { 0.0f, 0.0f };
        glm::vec2 scale = { 0.0f, 0.0f };
        float rotation = 0.0f;
        Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        RenderableLayerLevel layer = Layer::Game;
        float priority = 0.0f;
        bool visible = true;
    };

    class Renderable : public RefCounted
    {
    public:
        Renderable(const RenderableState& state);
        virtual ~Renderable();

        Renderable(const Renderable& other);

        virtual void render() const = 0;
        virtual Ref<Renderable> clone() const = 0;

        const RenderableState& getState() const { return state_; }

        const glm::vec2& getPosition() const { return state_.pos; }
        void setPosition(const glm::vec2& pos) { state_.pos = pos; updateTransform(); }

        const glm::vec2& getScale() const { return state_.scale; }
        void setScale(const glm::vec2& scale) { state_.scale = scale; updateTransform(); }

        float getRotation() const { return state_.rotation; }
        void setRotation(float rotation) { state_.rotation = rotation; updateTransform(); }

        const Color& getColor() const { return state_.color; }
        void setColor(const Color& color) { state_.color = color; }

        RenderableLayerLevel getLayer() const { return state_.layer; }
        void setLayer(RenderableLayerLevel layer);

        float getPriority() const { return state_.priority; }
        void setPriority(float priority) { state_.priority = priority; updateTransform(); }

        bool isVisible() const { return state_.visible; }
        void setVisible(bool visible) { state_.visible = visible; }

        ShaderRef getShader() const { return shader_; }
        const std::string& getShaderName() const { return shaderName_; }

        void setShader(const std::string& name);

        const glm::mat4& getTransform() const { return transform_; }

    private:
        void updateTransform();

    private:
        ShaderRef shader_;
        std::string shaderName_;

        glm::mat4 transform_;

        RenderableState state_;
    };
}