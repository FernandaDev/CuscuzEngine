#pragma once

#define BIT(x) (1 << x)

#define BIND_FUNCTION(instance, func) std::bind(&func, instance, std::placeholders::_1)

enum
{
    SCREEN_WIDTH = 1280,
    SCREEN_HEIGHT = 720
};