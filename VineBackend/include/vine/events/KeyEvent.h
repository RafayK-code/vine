#pragma once

#include <vine/events/Event.h>
#include <vine/core/codes/KeyCodes.h>

namespace vine
{
    class KeyEvent : public Event<KeyEvent>
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
        KeyDownEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }
    };

    class KeyHeldEvent : public KeyEvent
    {
    public:
        KeyHeldEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }
    };

    class KeyUpEvent : public KeyEvent
    {
    public:
        KeyUpEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }
    };

    class KeyTypedEvent : public Event<KeyTypedEvent>
    {
    public:
        KeyTypedEvent(const std::string& text)
            : text_(text)
        {
        }

        const std::string& getText() const { return text_; }

    private:
        std::string text_;
    };
}