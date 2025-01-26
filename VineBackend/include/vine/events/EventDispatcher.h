#pragma once

#include <vine/events/Event.h>

#include <functional>
#include <vector>

namespace vine
{
    template<typename E>
    using EventCallbackFn = std::function<void(E&)>;

    class EventDispatcher
    {
    public:
        EventDispatcher();
        virtual ~EventDispatcher();

        using CallbackID = uint64_t;

        template<typename E>
        CallbackID addEventCallback(const EventCallbackFn<E>& callback)
        {
            BaseEventCallbackFn cbWrapper = [callback](AbstractEvent* e)
            {
                if (E* event = dynamic_cast<E*>(e))
                    callback(*event);
            };

            uint32_t index = E::getEventTypeID();
            if (index >= callbackFns_.size())
                callbackFns_.resize(index + 1);

            callbackFns_[index].push_back(cbWrapper);
            return generateCallbackID<E>();
        }

        void removeEventCallback(CallbackID callback);

    protected:
        template<typename E>
        void dispatchEvent(E& e)
        {
            uint32_t index = E::getEventTypeID();
            if (index >= callbackFns_.size())
                return;

            std::vector<BaseEventCallbackFn> eCallbacks = callbackFns_[index];
            for (const auto& callback : eCallbacks)
            {
                callback(&e);
            }
        }

    private:
        template<typename E>
        CallbackID generateCallbackID()
        {
            uint32_t high = E::getEventTypeID();
            uint32_t low = callbackFns_[E::getEventTypeID()].size() - 1;

            return ((CallbackID)high << 32) | low;
        }

        using BaseEventCallbackFn = std::function<void(AbstractEvent*)>;

    private:
        using CallbackList = std::vector<std::vector<BaseEventCallbackFn>>;
        CallbackList callbackFns_;
    };
}