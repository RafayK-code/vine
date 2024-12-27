#pragma once

#include <vine/window/Window.h>

namespace vine
{
    class GraphicsContext
    {
    public:
        GraphicsContext();
        ~GraphicsContext();

        void createContext(Window* window);
        void destroyContext();

        SDL_GLContext getContext() const { return context_; }

    private:
        SDL_GLContext context_;
    };
}