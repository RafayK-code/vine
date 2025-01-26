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
        KeyDownEvent(KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), repeat_(isRepeat)
        {
        }

        bool isRepeat() const { return repeat_; }

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