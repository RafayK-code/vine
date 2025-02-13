#include <vine/events/EventListener.h>

#include <vine/events/EventDispatcher.h>

namespace vine
{
    EventListener::EventListener()
    {
    }

    EventListener::~EventListener()
    {
        stopListening();
    }

    void EventListener::stopListening()
    {
        for (EventDispatcher* dispatcher : dispatchers_)
        {
            stopListening(*dispatcher);
        }
    }

    void EventListener::stopListening(EventDispatcher& dispatcher)
    {
        auto it = dispatchers_.find(&dispatcher);
        if (it == dispatchers_.end())
            return;

        dispatcher.removeListener(this);
        callbacks_[&dispatcher].clear();
    }

    void EventListener::handleEvent(EventDispatcher* dispatcher, const AbstractEvent* event)
    {
        auto it = callbacks_[dispatcher].find(event->getThisEventTypeID());
        if (it != callbacks_[dispatcher].end())
            it->second(event);
    }

    void EventListener::eventDispatcherDestroyed(EventDispatcher* dispatcher)
    {
        callbacks_.erase(dispatcher);
        dispatchers_.erase(dispatcher);
    }
}