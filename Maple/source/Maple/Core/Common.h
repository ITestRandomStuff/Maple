#pragma once

#define MPL_BIND_CALLBACK_FUNCTION(func) [&](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }

namespace Maple
{
    template<typename Ty>
    using ScopePtr = std::unique_ptr<Ty>;

    template<typename Ty>
    using RefPtr = std::shared_ptr<Ty>;

    template<typename Ty, typename... Args>
    inline ScopePtr<Ty> MakeScope(Args&&... args)
    {
        return std::make_unique<Ty>(std::forward<Args>(args)...);
    }

    template<typename Ty, typename... Args>
    inline RefPtr<Ty> MakeRef(Args&&... args)
    {
        return std::make_shared<Ty>(std::forward<Args>(args)...);
    }
}

#include "Maple/Debug/Log.h"