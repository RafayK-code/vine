#pragma once

#include <vine/events/Event.h>
#include <vine/core/codes/MouseCodes.h>

namespace vine
{
    class MouseButtonEvent : public Event<MouseButtonEvent>
    {
    public:
        MouseCode getMouseButton() const { return button_; }

        float getX() const { return mouseX_; }
        float getY() const { return mouseY_; }

    protected:
        MouseButtonEvent(MouseCode button, float x, float y)
            : button_(button), mouseX_(x), mouseY_(y)
        {
        }

        MouseCode button_;
        float mouseX_;
        float mouseY_;
    };

    class MouseButtonDownEvent : public MouseButtonEvent
    {
    public:
        MouseButtonDownEvent(MouseCode button, float x, float y)
            : MouseButtonEvent(button, x, y)
        {
        }
    };

    class MouseButtonUpEvent : public MouseButtonEvent
    {
    public:
        MouseButtonUpEvent(MouseCode button, float x, float y)
            : MouseButtonEvent(button, x, y)
        {
        }
    };

    class MouseMovedEvent : public Event<MouseMovedEvent>
    {
    public:
        MouseMovedEvent(float x, float y)
            : mouseX_(x), mouseY_(y)
        {
        }

        float getX() const { return mouseX_; }
        float getY() const { return mouseY_; }

    private:
        float mouseX_;
        float mouseY_;
    };

    class MouseScrolledEvent : public Event<MouseMovedEvent>
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : xOffset_(xOffset), yOffset_(yOffset)
        {
        }

        float getXOffset() const { return xOffset_; }
        float getYOffset() const { return yOffset_; }

    private:
        float xOffset_;
        float yOffset_;
    };
}