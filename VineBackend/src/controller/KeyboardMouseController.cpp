#include <vine/controller/KeyboardMouseController.h>

#include <vine/events/KeyEvent.h>
#include <vine/events/MouseEvent.h>

namespace vine
{
    KeyboardMouseController::KeyboardMouseController()
        : state_(State::Default)
    {
        SDL_StopTextInput();
    }

    KeyboardMouseController::~KeyboardMouseController()
    {
    }

    void KeyboardMouseController::dispatchSDLEvents(const SDL_Event* event)
    {
        switch (event->type)
        {
        case SDL_KEYDOWN:
        {
            if (!event->key.repeat)
            {
                KeyDownEvent e(event->key.keysym.sym);
                dispatchEvent(e);
            }
            else
            {
                KeyHeldEvent e(event->key.keysym.sym);
                dispatchEvent(e);
            }
            break;
        }
        case SDL_KEYUP:
        {
            KeyUpEvent e(event->key.keysym.sym);
            dispatchEvent(e);
            break;
        }
        case SDL_TEXTINPUT:
        {
            KeyTypedEvent e(event->text.text);
            dispatchEvent(e);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            MouseButtonDownEvent e(event->button.button, event->button.x, event->button.y);
            dispatchEvent(e);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            MouseButtonUpEvent e(event->button.button, event->button.x, event->button.y);
            dispatchEvent(e);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            MouseMovedEvent e(event->motion.x, event->motion.y);
            dispatchEvent(e);
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            MouseScrolledEvent e(event->wheel.x, event->wheel.y);
            dispatchEvent(e);
            break;
        }
        }
    }

    bool KeyboardMouseController::isKeyDown(KeyCode key) const
    {
        const uint8_t* state = SDL_GetKeyboardState(nullptr);
        SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
        return state[scancode] != 0;
    }

    bool KeyboardMouseController::isMouseButtonDown(MouseCode button) const
    {
        uint32_t mouseState = SDL_GetMouseState(nullptr, nullptr);
        return (mouseState & SDL_BUTTON(button)) != 0;
    }

    Vec2 KeyboardMouseController::getMousePos() const
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        return { (float)x, (float)y };
    }

    void KeyboardMouseController::setState(State state)
    {
        switch (state)
        {
        case State::Default:
            if (state_ == State::Typing)
                SDL_StopTextInput();
            break;
        case State::Typing:
            if (state_ != State::Typing)
                SDL_StartTextInput();
            break;
        }

        state_ = state;
    }
}