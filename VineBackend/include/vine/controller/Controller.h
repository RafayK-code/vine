#pragma once

#include <vine/events/Event.h>

#include <SDL.h>

namespace vine
{
    class Controller : public EventDispatcher
    {
    public:
        Controller();
        ~Controller();

        virtual void dispatchSDLEvents(const SDL_Event* event) = 0;

        enum class Type
        {
            Keyboard,
            Console,
            Unknown
        };

        virtual Type getType() const = 0;
    };
}