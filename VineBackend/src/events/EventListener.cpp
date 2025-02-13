#include <vine/events/EventListener.h>

#include <vine/events/EventDispatcher.h>

namespace vine
{
    EventListener::EventListener(EventDispatcher& dispatcher)
        : dispatcher_(&dispatcher)
    {
    }

    EventListener::~EventListener()
    {
        stopListening();
    }

    void EventListener::stopListening()
    {
        if (!dispatcher_)
            return;

        dispatcher_->removeListener(this);
        callbacks_.clear();
    }

    void EventListener::handleEvent(const AbstractEvent* event)
    {
        auto it = callbacks_.find(event->getThisEventTypeID());
        if (it != callbacks_.end())
            it->second(event);
    }

    void EventListener::eventDispatcherDestroyed()
    {
        callbacks_.clear();
        dispatcher_ = nullptr;
    }
}