#pragma once

#include <SDL_mouse.h>

namespace vine
{
    using MouseCode = uint8_t;

    namespace Mouse
    {
        enum : MouseCode
        {
            LeftButton = SDL_BUTTON_LEFT,
            RightButton = SDL_BUTTON_RIGHT,
            MiddleButton = SDL_BUTTON_MIDDLE,
            SideButton1 = SDL_BUTTON_X1,
            SideButton2 = SDL_BUTTON_X2,
        };
    }
}