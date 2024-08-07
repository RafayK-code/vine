#pragma once

#include <memory>

namespace vine
{
    template<typename T>
    using ScopePtr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr ScopePtr<T> makeScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using RefPtr = std::shared_ptr<T>;

    template<typename T, typename... Args>
    constexpr RefPtr<T> makeRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}