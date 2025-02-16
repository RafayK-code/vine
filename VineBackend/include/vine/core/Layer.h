#pragma once

#include <cstdint>

namespace vine
{
    using LayerLevel = uint32_t;

    namespace Layer
    {
        enum : uint32_t
        {
            Background = 6,
            CG = 5,
            Game = 4,
            Foreground = 3,
            Effects = 2,
            UI = 1,
        };
    }
}