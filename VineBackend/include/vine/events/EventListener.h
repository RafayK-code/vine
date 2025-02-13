#pragma once

#include <vine/events/Event.h>

#include <vector>
#include <map>
#include <set>

namespace vine
{
    class EventDispatcher;

    class EventListener
    {
    public:
        EventListener();
        ~EventListener();

        template <typename E>
        void listen(EventDispatcher& dispatcher, const EventCallbackFn<E>& callback)
        {
            auto wrapper = [callback](const AbstractEvent* event)
            {
                if (const E* e = dynamic_cast<const E*>(event))
                    callback(*e);
            };

            auto it = dispatchers_.find(&dispatcher);
            if (it == dispatchers_.end())
                dispatchers_.insert(&dispatcher);

            dispatcher.addListener<E>(this);
            callbacks_[&dispatcher][E::getEventTypeID()] = wrapper;
        }

        template <typename E>
        void stopListeningForEvent()
        {
            for (EventDispatcher* dispatcher : dispatchers_)
            {
                stopListeningForEvent<E>(*dispatcher);
            }
        }

        template <typename E>
        void stopListeningForEvent(EventDispatcher& dispatcher)
        {
            auto it = dispatchers_.find(&dispatcher);
            if (it == dispatchers_.end())
                return;

            dispatcher.removeListenerForEvent<E>(this);
            callbacks[&dispatcher].erase(E::getEventTypeID());
        }

        void stopListening();
        void stopListening(EventDispatcher& dispatcher);

    private:
        friend class EventDispatcher;

        void handleEvent(EventDispatcher* dispatcher, const AbstractEvent* event);
        void eventDispatcherDestroyed(EventDispatcher* dispatcher);

    private:
        using BaseEventCallbackFn = std::function<void(const AbstractEvent*)>;
        using EventCallbackMap = std::map<EventDispatcher*, std::map<uint32_t, BaseEventCallbackFn>>;

        EventCallbackMap callbacks_;
        std::set<EventDispatcher*> dispatchers_;
    };
}