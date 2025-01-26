#pragma once

#include <vine/events/Event.h>

namespace vine
{
    class WindowCloseEvent : public Event<WindowCloseEvent>
    {
    public:
        WindowCloseEvent() = default;
    };

    class WindowResizeEvent : public Event<WindowResizeEvent> 
    {
    public:
        WindowResizeEvent(int width, int height)
            : width_(width), height_(height)
        {
        }

        int getWidth() const { return width_; }
        int getHeight() const { return height_; }

    private:
        int width_;
        int height_;
    };

    class WindowFocusEvent : public Event<WindowFocusEvent>
    {
    public:
        WindowFocusEvent() = default;

    };

    class WindowLostFocusEvent : public Event<WindowLostFocusEvent>
    {
    public:
        WindowLostFocusEvent() = default;
    };

    class WindowMovedEvent : public Event<WindowMovedEvent>
    {
    public:
        WindowMovedEvent(int xpos, int ypos)
            : xpos_(xpos), ypos_(ypos)
        {
        }

        int getXPos() const { return xpos_; }
        int getYPos() const { return ypos_; }

    private:
        int xpos_;
        int ypos_;
    };
}