#pragma once

#include <vine/renderer/backend/Shader.h>

#include <glm/glm.hpp>
#include <string>

namespace vine
{
    struct RenderableState
    {
        glm::vec2 pos = { 0.0f, 0.0f };
        glm::vec2 scale = { 0.0f, 0.0f };
        float rotation = 0.0f;
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
        float layer = 1;    // Used as z axis potentially
        bool visible = true;
    };

    class Renderable
    {
    public:
        Renderable(const RenderableState& state);
        virtual ~Renderable();

        virtual void render() const = 0;

        const glm::vec2& getPosition() const { return state_.pos; }
        void setPosition(const glm::vec2& pos) { state_.pos = pos; updateTransform(); }

        const glm::vec2& getScale() const { return state_.scale; }
        void setScale(const glm::vec2& scale) { state_.scale = scale; updateTransform(); }

        float getRotation() const { return state_.rotation; }
        void setRotation(float rotation) { state_.rotation = rotation; updateTransform(); }

        const glm::vec4& getColor() const { return state_.color; }
        void setColor(const glm::vec4& color) { state_.color = color; }

        float getLayer() const { return state_.layer; }
        void setLayer(float layer) { state_.layer = layer; updateTransform(); }

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