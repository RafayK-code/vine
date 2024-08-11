#pragma once

#include <functional>
#include <vector>
#include <string>

namespace vine
{
    enum EventType
    {
        None = -1,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppRender,
        KeyDown, KeyUp, KeyTyped,
        MouseButtonDown, MouseButtonUp, MouseMoved, MouseScrolled,
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType getEventType() const = 0;
        virtual std::string getName() const = 0;
    };

    template<typename E>
    using EventCallbackFn = std::function<void(E&)>;
    
    using CallbackID = uint64_t;

    class EventDispatcher
    {
    public:
        EventDispatcher();
        ~EventDispatcher();

        template<typename E>
        CallbackID addEventCallback(const EventCallbackFn<E>& callback)
        {
            BaseEventCallbackFn cbWrapper = [callback](Event* e)
            {
                if (E* event = dynamic_cast<E*>(e))
                    callback(*event);
            };

            callbackFns_[E::getStaticEventType()].push_back(cbWrapper);
            return generateCallbackID<E>();
        }

        void removeEventCallback(CallbackID callback);

    protected:
        template<typename E>
        void dispatchEvent(E& e)
        {
            std::vector<BaseEventCallbackFn> eCallbacks = callbackFns_[E::getStaticEventType()];
            for (const auto& callback : eCallbacks)
            {
                callback(&e);
            }
        }

    private:
        template<typename E>
        CallbackID generateCallbackID()
        {
            uint32_t high = E::getStaticEventType();
            uint32_t low = callbackFns_[E::getStaticEventType()].size() - 1;

            return ((CallbackID)high << 32) | low;
        }

        using BaseEventCallbackFn = std::function<void(Event*)>;

    private:
        std::vector<std::vector<BaseEventCallbackFn>> callbackFns_;
    };
}