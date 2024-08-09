#pragma once

#include <SDL.h>

namespace vine
{
    class GraphicsContext
    {
    public:
        GraphicsContext();
        ~GraphicsContext();

        void createContext(SDL_Window* window);
        void destroyContext();

    private:
        SDL_GLContext context_;
    };
}