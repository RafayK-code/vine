#pragma once

#include <vine/events/Event.h>
#include <vine/core/codes/KeyCodes.h>

namespace vine
{
    class KeyEvent : public Event
    {
    public:
        KeyCode getKeyCode() const { return keyCode_; }

    protected:
        KeyEvent(KeyCode keycode)
            : keyCode_(keycode)
        {
        }

        KeyCode keyCode_;
    };

    class KeyDownEvent : public KeyEvent
    {
    public:
        KeyDownEvent(KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), repeat_(isRepeat)
        {
        }

        bool isRepeat() const { return repeat_; }

        EventType getEventType() const override { return EventType::KeyDown; }
        static EventType getStaticEventType() { return EventType::KeyDown; }
        std::string getName() const override { return "KeyDownEvent"; }

    private:
        bool repeat_;
    };

    class KeyUpEvent : public KeyEvent
    {
    public:
        KeyUpEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }

        EventType getEventType() const override { return EventType::KeyUp; }
        static EventType getStaticEventType() { return EventType::KeyUp; }
        std::string getName() const override { return "KeyUpEvent"; }
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }

        EventType getEventType() const override { return EventType::KeyTyped; }
        static EventType getStaticEventType() { return EventType::KeyTyped; }
        std::string getName() const override { return "KeyTypedEvent"; }
    };
}