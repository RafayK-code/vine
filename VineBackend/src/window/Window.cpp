#include <vine/window/Window.h>

namespace vine
{
    Window::Window(const WindowProps& props)
        : window_(nullptr), props_(props)
    {
        init();
    }

    Window::~Window()
    {
        destroy();
    }

    void Window::init()
    {
        window_ = SDL_CreateWindow(props_.title.c_str(), props_.xpos, props_.ypos, props_.width, props_.height, 0);
    }

    void Window::dispatchSDLEvents(const SDL_Event* event)
    {

        switch (event->window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            props_.width = event->window.data1;
            props_.height = event->window.data2;
            break;
        case SDL_WINDOWEVENT_MOVED:
            props_.xpos = event->window.data1;
            props_.ypos = event->window.data2;
            break;
        }
    }
}