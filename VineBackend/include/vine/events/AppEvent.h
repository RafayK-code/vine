#pragma once

#include <vine/events/Event.h>

namespace vine
{
    class AppTickEvent : public Event<AppTickEvent>
    {
    public:
        AppTickEvent(float dt)
            : dt_(dt)
        {
        }

        float getDt() const { return dt_; }

    private:
        float dt_;
    };

    class AppRenderEvent : public Event<AppRenderEvent>
    {
    public:
        AppRenderEvent() = default;
    };
}