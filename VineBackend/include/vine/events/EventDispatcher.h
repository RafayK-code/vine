#pragma once

#include <vine/events/Event.h>
#include <vine/events/EventListener.h>
#include <vine/sys/Ref.h>

#include <functional>
#include <algorithm>
#include <vector>
#include <map>

namespace vine
{
    class EventDispatcher
    {
    public:
        EventDispatcher();
        virtual ~EventDispatcher();

        template <typename E>
        void addListener(EventListener* listener)
        {
            removeListenerForEvent<E>(listener);
            listeners_[E::getEventTypeID()].push_back(listener);
        }

        template <typename E>
        void removeListenerForEvent(EventListener* listener)
        {
            std::vector<EventListener*>& vec = listeners_[E::getEventTypeID()];
            auto it = std::find(vec.begin(), vec.end(), listener);
            if (it != vec.end())
                vec.erase(it);
        }

        void removeListener(EventListener* listener)
        {
            for (auto& pair : listeners_)
            {
                std::vector<EventListener*>& vec = pair.second;
                auto it = std::find(vec.begin(), vec.end(), listener);
                if (it != vec.end())
                    vec.erase(it);
            }
        }

        template<typename E>
        void dispatchEvent(const E& e)
        {
            auto it = listeners_.find(E::getEventTypeID());
            if (it == listeners_.end())
                return;

            for (EventListener* listener : it->second)
                listener->handleEvent(&e);
        }

    private:
        using ListenerMap = std::map<uint32_t, std::vector<EventListener*>>;
        ListenerMap listeners_;
    };
}