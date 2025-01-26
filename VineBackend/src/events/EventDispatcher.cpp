#include <vine/events/EventDispatcher.h>

static constexpr int MAX_EVENTS = 14;

namespace vine
{
    EventDispatcher::EventDispatcher()
    {
    }

    EventDispatcher::~EventDispatcher()
    {
    }

    void EventDispatcher::removeEventCallback(CallbackID callback)
    {
        uint32_t high = callback >> 32;
        uint32_t low = (uint32_t)callback;

        callbackFns_[high].erase(callbackFns_[high].begin() + low);
    }
}