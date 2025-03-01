#pragma once

#include <memory>

#ifdef CC_ENABLE_ASSERT
#define CC_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
        #define CC_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_FUNCTION(instance, func) std::bind(&func, instance, std::placeholders::_1)

enum
{
    SCREEN_WIDTH = 1280,
    SCREEN_HEIGHT = 720,
    HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2,
    HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2,
};

namespace Cuscuz
{
    template<typename T>
    using CC_AssetRef = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr CC_AssetRef<T> CreateAssetRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}
