#pragma once

#include <vine/events/Event.h>

namespace vine
{
    class AppTickEvent : public Event
    {
    public:
        AppTickEvent(float dt)
            : dt_(dt)
        {
        }

        float getDt() const { return dt_; }

        EventType getEventType() const override { return EventType::AppTick; }
        static EventType getStaticEventType() { return EventType::AppTick; }
        std::string getName() const override { return "AppTickEvent"; }

    private:
        float dt_;
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EventType getEventType() const override { return EventType::AppRender; }
        static EventType getStaticEventType() { return EventType::AppRender; }
        std::string getName() const override { return "AppRenderEvent"; }
    };
}