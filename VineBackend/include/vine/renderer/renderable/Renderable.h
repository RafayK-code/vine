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

    enum class HAnchor
    {
        Left,
        Center,
        Right,
    };

    enum class VAnchor
    {
        Bottom,
        Center,
        Top,
    };

    struct RenderableState
    {
        glm::vec2 pos = { 0.0f, 0.0f };
        glm::vec2 size = { 1.0f, 1.0f };
        glm::vec2 scale = { 1.0f, 1.0f };
        float rotation = 0.0f;
        Color color = { 1.0f, 1.0f, 1.0f, 1.0f };
        RenderableLayerLevel layer = Layer::Game;
        float priority = 0.0f;
        bool visible = true;
        VAnchor vAnchor = VAnchor::Center;
        HAnchor hAnchor = HAnchor::Center;
        Vec2 pivot = { 0.5f, 0.5f };
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

        const Vec2& getPosition() const { return state_.pos; }
        void setPosition(const Vec2& pos) { state_.pos = pos; updateTransform(); }

        const Vec2& getSize() const { return state_.size; }
        void setSize(const Vec2& size) { state_.size = size; updateTransform(); }

        const Vec2& getScale() const { return state_.scale; }
        void setScale(const Vec2& scale) { state_.scale = scale; updateTransform(); }

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

        HAnchor getHAnchor() const { return state_.hAnchor; }
        void setHAnchor(HAnchor hAnchor) { state_.hAnchor = hAnchor; updateTransform(); }

        VAnchor getVAnchor() const { return state_.vAnchor; }
        void setVAnchor(VAnchor vAnchor) { state_.vAnchor = vAnchor; updateTransform(); }

        const Vec2& getPivot() const { return state_.pivot; }
        void setPivot(const Vec2& pivot) { state_.pivot = pivot; updateTransform(); }

        ShaderRef getShader() const { return shader_; }
        const std::string& getShaderName() const { return shaderName_; }

        void setShader(const std::string& name);

        const glm::mat4& getTransform() const { return transform_; }

    protected:
        void updateTransform();

    protected:
        ShaderRef shader_;
        std::string shaderName_;

        glm::mat4 transform_;

        RenderableState state_;
    };
}