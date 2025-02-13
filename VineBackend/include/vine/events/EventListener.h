#pragma once

#include <vine/events/Event.h>

#include <vector>
#include <map>

namespace vine
{
    class EventDispatcher;

    class EventListener
    {
    public:
        EventListener(EventDispatcher& dispatcher);
        ~EventListener();

        template <typename E>
        void listen(const EventCallbackFn<E>& callback)
        {
            if (!dispatcher_)
                return;

            auto wrapper = [callback](const AbstractEvent* event)
            {
                if (const E* e = dynamic_cast<const E*>(event))
                    callback(*e);
            };

            dispatcher_->addListener<E>(this);
            callbacks_[E::getEventTypeID()] = wrapper;
        }

        template <typename E>
        void stopListeningForEvent()
        {
            if (!dispatcher_)
                return;

            dispatcher_->removeListenerForEvent<E>(this);
            callbacks_.erase(E::getEventTypeID());
        }

        void stopListening();

    private:
        friend class EventDispatcher;

        void handleEvent(const AbstractEvent* event);
        void eventDispatcherDestroyed();

    private:
        using BaseEventCallbackFn = std::function<void(const AbstractEvent*)>;
        using EventCallbackMap = std::map<uint32_t, BaseEventCallbackFn>;

        EventCallbackMap callbacks_;
        EventDispatcher* dispatcher_;
    };
}