#pragma once

#include <vine/renderer/renderable/Renderable.h>

#include <vine/util/Math.h>

namespace vine
{
    template <typename B>
    class RenderableBuilder
    {
    public:
        RenderableBuilder();
        virtual ~RenderableBuilder();

        virtual Ref<Renderable> create() const = 0;

        B& setPosition(const Vec2& pos);
        B& setScale(const Vec2& scale);
        B& setRotation(float rotation);
        B& setColor(const Color& color);
        B& setLayer(RenderableLayerLevel layer);
        B& setPriority(float priority);
        B& setVisible(bool visible);

    protected:
        RenderableState state_;
    };

    template<typename B, typename T>
    class RenderableBuilderT : public RenderableBuilder<B>
    {
    public:
        Ref<T> createT() const { return create().dynamicCast<T>(); }
    };

    template <typename B>
    RenderableBuilder<B>::RenderableBuilder()
        : state_(RenderableState())
    {
    }

    template <typename B>
    RenderableBuilder<B>::~RenderableBuilder()
    {
    }

    template <typename B>
    B& RenderableBuilder<B>::setPosition(const Vec2& pos)
    {
        state_.pos = pos;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setScale(const Vec2& scale)
    {
        state_.scale = scale;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setRotation(float rotation)
    {
        state_.rotation = rotation;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setColor(const Color& color)
    {
        state_.color = color;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setLayer(RenderableLayerLevel layer)
    {
        state_.layer = layer;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setPriority(float priority)
    {
        state_.priority = priority;
        return static_cast<B&>(*this);
    }

    template <typename B>
    B& RenderableBuilder<B>::setVisible(bool visible)
    {
        state_.visible = visible;
        return static_cast<B&>(*this);
    }
}