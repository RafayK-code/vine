#pragma once

namespace vine
{
    enum class TweenLoopType
    {
        Restart,
        PingPong,
    };

    enum class TweenState
    {
        None,
        Running,
        Paused,
        Completed,
        Destroyed,
    };
}