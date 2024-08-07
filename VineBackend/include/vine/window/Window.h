#pragma once

#include <vine/events/Event.h>

#include <SDL.h>

namespace vine
{
    struct WindowProps
    {
        std::string title;

        uint32_t xpos;
        uint32_t ypos;

        uint32_t width;
        uint32_t height;
    };

    class Window : public EventDispatcher
    {
    public:
        Window(const WindowProps& props);
        ~Window();

        void tick();

        const std::string& getTitle() const { return props_.title; }

        uint32_t getXPos() const { return props_.xpos; }
        uint32_t getYPos() const { return props_.ypos; }

        uint32_t getWidth() const { return props_.width; }
        uint32_t getHeight() const { return props_.height; }

        // SDL functions

        void dispatchSDLEvents(const SDL_Event* event);
        SDL_Window* getNativePtr() const { return window_; }

    private:
        void init();
        void destroy();

    private:
        SDL_Window* window_;

        WindowProps props_;
    };
}