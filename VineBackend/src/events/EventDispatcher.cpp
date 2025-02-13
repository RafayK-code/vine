#include <vine/events/EventDispatcher.h>

namespace vine
{
    EventDispatcher::EventDispatcher()
    {
    }

    EventDispatcher::~EventDispatcher()
    {
        for (auto& pair : listeners_)
        {
            for (EventListener* listener : pair.second)
                listener->eventDispatcherDestroyed(this);
        }
    }
}