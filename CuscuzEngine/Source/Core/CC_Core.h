#pragma once

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
    SCREEN_HEIGHT = 720
};