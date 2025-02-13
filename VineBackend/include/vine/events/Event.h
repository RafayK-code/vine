#pragma once

#include <functional>
#include <vector>
#include <string>

namespace vine
{
    class AbstractEvent
    {
    public:
        AbstractEvent() = default;
        virtual ~AbstractEvent() = default;

        virtual uint32_t getThisEventTypeID() const = 0;

    protected:

        static uint32_t getNewEventTypeID()
        {
            static uint32_t newID = 0;
            return newID++;
        }
    };

    template <typename T>
    class Event : public AbstractEvent
    {
    public:
        Event() = default;
        virtual ~Event() = default;

        uint32_t getThisEventTypeID() const override
        {
            return Event::getEventTypeID();
        }

        static uint32_t getEventTypeID()
        {
            static uint32_t typeID = getNewEventTypeID();
            return typeID;
        }
    };

    template<typename E>
    using EventCallbackFn = std::function<void(const E&)>;
}